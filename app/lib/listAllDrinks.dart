import 'dart:io';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:image_picker/image_picker.dart';
import 'package:mlkit/mlkit.dart';
import 'package:smartmix/UI/confirmModal.dart';
import 'package:smartmix/main.dart';

import 'newDrinkModal.dart';

class ListDrinks extends StatefulWidget {
  ListDrinks({Key key}) : super(key: key);

  _ListDrinksState createState() => _ListDrinksState();
}

class _ListDrinksState extends State<ListDrinks> {
  FlutterBluetoothSerial bluetooth = FlutterBluetoothSerial.instance;
  Firestore db = Firestore.instance;

  List<BluetoothDevice> _devices = [];
  BluetoothDevice _device;
  bool _connected = false;
  bool _pressed = false;
  bool ofAge = false;
  File _file;
  FirebaseVisionTextDetector textDetector = FirebaseVisionTextDetector.instance;
  static final TextEditingController _message = new TextEditingController();
  static final TextEditingController _text = new TextEditingController();

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  Future<void> initPlatformState() async {
    List<BluetoothDevice> devices = [];

    try {
      devices = await bluetooth.getBondedDevices();
    } catch (e) {}

    bluetooth.onStateChanged().listen((state) {
      switch (state) {
        case FlutterBluetoothSerial.CONNECTED:
          setState(() {
            _connected = true;
            _pressed = false;
          });
          break;
        case FlutterBluetoothSerial.DISCONNECTED:
          setState(() {
            _connected = false;
            _pressed = false;
          });
          break;
        default:
          print(state);
          break;
      }
    });

    bluetooth.onRead().listen((msg) {
      setState(() {
        print('Read: $msg');
        _text.text += msg;
      });
    });

    if (!mounted) return;
    setState(() {
      _devices = devices;
    });
  }

  List<DropdownMenuItem<BluetoothDevice>> _getDeviceItems() {
    List<DropdownMenuItem<BluetoothDevice>> items = [];
    if (_devices.isEmpty) {
      items.add(DropdownMenuItem(
        child: Text('NONE'),
      ));
    } else {
      _devices.forEach((device) {
        items.add(DropdownMenuItem(
          child: Text(device.name),
          value: device,
        ));
      });
    }
    return items;
  }

  void _connect() {
    if (_device == null) {
      show('No device selected.');
    } else {
      bluetooth.isConnected.then((isConnected) {
        if (!isConnected) {
          bluetooth.connect(_device).catchError((error) {
            setState(() => _pressed = false);
          });
          setState(() => _pressed = true);
        }
      });
    }
  }

  void _disconnect() {
    bluetooth.disconnect();
    setState(() => _pressed = true);
  }

  void _writeTest() {
    bluetooth.isConnected.then((isConnected) {
      if (isConnected) {
        bluetooth.write(_message.text);
      }
    });
  }

  Future<void> openCamera() async {
    var file = await ImagePicker.pickImage(source: ImageSource.camera);
    setState(() {
      _file = file;
    });
  }

  void confirmModal(bool check) {
    Navigator.of(context).push(
      PageRouteBuilder(
        opaque: false,
        pageBuilder: (BuildContext context, _, __) => ConfirmModal(
              valid: check,
            ),
      ),
    );
  }

  Future<void> scanID() async {
    var labels = await textDetector.detectFromPath(_file.path);

    labels.forEach((res) {
      if (res.text.contains('AGE')) {
        var temp = res.text.split(" ");

        if (int.parse(temp.last) < 2019) {
          setState(() {
            ofAge = true;
          });
          confirmModal(true);
        } else {
          setState(() {
            ofAge = false;
          });
          confirmModal(false);
        }
      } else if (res.text.contains('DOB')) {
        var temp = res.text.split("/");
        temp = temp.last.split("\n");

        if (int.parse(temp[0]) < 1998) {
          setState(() {
            ofAge = true;
          });
          confirmModal(true);
        } else {
          setState(() {
            ofAge = false;
          });
          confirmModal(false);
        }
      }
    });
  }

  Future<bool> verifyID() async {
    bool result = false;

    await openCamera();
    if (_file != null) {
      await scanID();
      setState(() {
        _file = null;
      });

      return ofAge;
    }
    return result;
  }

  Future show(
    String message, {
    Duration duration: const Duration(seconds: 3),
  }) async {
    await new Future.delayed(new Duration(milliseconds: 100));
    Scaffold.of(context).showSnackBar(
      new SnackBar(
        content: new Text(
          message,
          style: new TextStyle(
            color: Colors.white,
          ),
        ),
        duration: duration,
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('All Drinks'),
        actions: <Widget>[
          IconButton(
            icon: Icon(Icons.add),
            onPressed: () async {
              Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (BuildContext context) {
                      return AddNewDrink();
                    },
                    fullscreenDialog: true,
                  ));
            },
          ),
          Padding(
            padding: const EdgeInsets.fromLTRB(10.0, 10.0, 10.0, 0.0),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[],
            ),
          ),
        ],
      ),
      drawer: Drawer(
        child: Column(children: <Widget>[
          UserAccountsDrawerHeader(
            accountName: Text('Test User'),
            currentAccountPicture: CircleAvatar(
              backgroundImage: NetworkImage(
                  'https://images.unsplash.com/photo-1518806118471-f28b20a1d79d?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&w=1000&q=80'),
            ),
            accountEmail: Text('test@test.com'),
            decoration: BoxDecoration(
                image: DecorationImage(
                    fit: BoxFit.cover,
                    image: NetworkImage(
                      'http://sfwallpaper.com/images/technology-background-5.jpg',
                    ))),
          ),
          ListTile(
            title: Text('Home'),
            leading: Icon(Icons.home),
            onTap: () {
              Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) => MyHomePage(title: 'smartMix'),
                ),
              );
            },
          ),
          ListTile(
            title: Text('Create Mix'),
            leading: Icon(Icons.list),
            onTap: () {},
          ),
          ListTile(
            title: Text('All Drinks'),
            leading: Icon(Icons.star), // ----------- END OF WORK DONE BY SAUL
            onTap: () {
              Navigator.push(context,
                  MaterialPageRoute(builder: (context) => ListDrinks()));
            },
          ),
        ]),
      ),
      body: StreamBuilder(
        stream: db
            .collection('drinks')
            .where('uid', isEqualTo: 'aaa')
            .orderBy('createdAt', descending: true)
            .snapshots(),
        builder: (context, snap) {
          if (!snap.hasData) {
            return Center(child: CircularProgressIndicator());
          } else {
            var data = snap.data.documents;
            return data.length == 0
                ? Center(
                    child: Text(
                      'No custom drinks. Create one.',
                      style:
                          TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
                    ),
                  )
                : ListView.builder(
                    itemCount: data.length,
                    itemBuilder: (context, index) {
                      return ListTile(
                        leading: CircleAvatar(
                          backgroundImage: NetworkImage(
                              "https://hips.hearstapps.com/hmg-prod.s3.amazonaws.com/images/shutterstock-626261780mod-1515166546.jpg"),
                        ),
                        title: Text(data[index]['title']),
                        subtitle: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: <Widget>[
                            Text('Drink 1: ' + data[index]['tag'][0] + " Oz"),
                            Text('Drink 2: ' + data[index]['tag'][1] + " Oz"),
                            Text('Drink 3: ' + data[index]['tag'][2] + " Oz"),
                            Text('Total: ' + data[index]['total'].toString())
                          ],
                        ),
                        trailing: data[index]['restrict'] == true
                            ? Icon(Icons.error)
                            : null,
                        onTap: () {
                          showDialog(
                              context: context,
                              builder: (context) {
                                return data[index]['restrict'] == true
                                    ? AlertDialog(
                                        title: Text('Age Restriction'),
                                        content: Container(
                                          height: 100,
                                          child: SingleChildScrollView(
                                            child: Center(
                                              child: Column(
                                                mainAxisAlignment:
                                                    MainAxisAlignment.center,
                                                crossAxisAlignment:
                                                    CrossAxisAlignment.center,
                                                children: <Widget>[
                                                  SizedBox(
                                                    height: 10,
                                                  ),
                                                  Icon(Icons.error, size: 50),
                                                  Text(
                                                      'Must be 21 years or older to pour this drink. Verify age using ID.')
                                                ],
                                              ),
                                            ),
                                          ),
                                        ),
                                        actions: <Widget>[
                                          FlatButton(
                                            child: Text("Verify"),
                                            onPressed: () async {
                                              Navigator.of(context).pop();
                                              bool result = await verifyID();

                                              if (result) {
                                                _message.text =
                                                    data[index]['tag'];
                                                _writeTest();
                                              }
                                              setState(() {
                                                ofAge = false;
                                              });
                                            },
                                          ),
                                          FlatButton(
                                            child: Text('Cancel'),
                                            onPressed: () {
                                              Navigator.pop(context);
                                            },
                                          )
                                        ],
                                      )
                                    : AlertDialog(
                                        title: Text("Pour Order"),
                                        content: SingleChildScrollView(
                                          child: Column(
                                            mainAxisAlignment:
                                                MainAxisAlignment.spaceBetween,
                                            crossAxisAlignment:
                                                CrossAxisAlignment.center,
                                            children: <Widget>[
                                              Text('Drink 1: ' +
                                                  data[index]['tag'][0] +
                                                  ' Oz'),
                                              SizedBox(
                                                width: 5,
                                              ),
                                              Text('Drink 2: ' +
                                                  data[index]['tag'][1] +
                                                  ' Oz'),
                                              SizedBox(
                                                width: 5,
                                              ),
                                              Text('Drink 3: ' +
                                                  data[index]['tag'][2] +
                                                  ' Oz')
                                            ],
                                          ),
                                        ),
                                        actions: <Widget>[
                                          FlatButton(
                                            child: Text("Pour"),
                                            onPressed: () {
                                              _message.text =
                                                  data[index]['tag'];
                                              _writeTest();
                                              Navigator.pop(context);
                                            },
                                          ),
                                          FlatButton(
                                            child: Text('Cancel'),
                                            onPressed: () {
                                              Navigator.pop(context);
                                            },
                                          )
                                        ],
                                      );
                              });
                        },
                      );
                      // data[index]['title'], data[index]['tag'],
                      //   data[index]['restrict']);
                    },
                  );
          }
        },
      ),
    );
  }
}
