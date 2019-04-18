import 'package:flutter/material.dart';

import 'dart:async';
import 'package:flutter/services.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class AddNewDrink extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return AddNewDrinkState();
  }
}

class AddNewDrinkState extends State<AddNewDrink> {

  FlutterBluetoothSerial bluetooth = FlutterBluetoothSerial.instance;

  List<BluetoothDevice> _devices = [];
  BluetoothDevice _device;
  bool _connected = false;
  bool _pressed = false;

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
    } on PlatformException {
      // TODO - Error
    }

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
          // TODO
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

  ///
  ///
  ///
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

  ///
  ///
  ///
  void _disconnect() {
    bluetooth.disconnect();
    setState(() => _pressed = true);
  }

  ///
  ///
  ///
  void _writeTest() {
    bluetooth.isConnected.then((isConnected) {
      if (isConnected) {
        bluetooth.write(_message.text);
      }
    });
  }

  ///
  ///
  ///
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

  final _formKey = GlobalKey<FormState>();
  List<String> _colors = <String>['', 'red', 'green', 'blue', 'orange'];
  String _color = '';
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Add A Drink')),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          Form(
            key: _formKey,
            autovalidate: true,
            child: Column(
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 50.0),
                  child: TextFormField(
                    decoration: InputDecoration(
                      labelText: 'Drink Name',
                    ),
                    validator: (value) {
                      if (value.isEmpty) {
                        return 'Please Enter Drink Name';
                      }
                    },
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.symmetric(horizontal: 50.0),
                  child: FormField(
                    validator: (value) {
                      if (value == '') {
                        return 'Please choose drinks';
                      }
                    },
                    builder: (FormFieldState state) {
                      return InputDecorator(
                        decoration: InputDecoration(
                          labelText: 'Drinks',
                        ),
                        isEmpty: _color == '',
                        child: DropdownButtonHideUnderline(
                          child: DropdownButton(
                            value: _color,
                            isDense: true,
                            onChanged: (String newValue) {
                              setState(() {
                                _color = newValue;
                                state.didChange(newValue);
                              });
                            },
                            items: _colors.map((String value) {
                              return DropdownMenuItem(
                                value: value,
                                child: Text(value),
                              );
                            }).toList(),
                          ),
                        ),
                      );
                    },
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.symmetric(vertical: 16.0),
                  child: RaisedButton(
                    onPressed: () {
                      // Validate will return true if the form is valid, or false if
                      // the form is invalid.
                      if (_formKey.currentState.validate()) {
                        
                        Navigator.pop(context);
                        // If the form is valid, we want to show a Snackbar

                      }
                    },
                    child: Text('Submit'),
                  ),
                ),
                Container(
          child: ListView(
            shrinkWrap: true,
            children: <Widget>[
              Padding(
                padding: const EdgeInsets.fromLTRB(10.0, 10.0, 10.0, 0.0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: <Widget>[
                    Text(
                      'Device:',
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    DropdownButton(
                      items: _getDeviceItems(),
                      onChanged: (value) => setState(() => _device = value),
                      value: _device,
                    ),
                    RaisedButton(
                      onPressed:
                          _pressed ? null : _connected ? _disconnect : _connect,
                      child: Text(_connected ? 'Disconnect' : 'Connect'),
                    ),
                  ],
                ),
              ),
              Padding(
                padding: const EdgeInsets.fromLTRB(10.0, 6.0, 10.0, 0.0),
                child: Row(
                  children: <Widget>[
                    Expanded(
                      child: new TextField(
                        controller: _message,
                        autocorrect: false,
                        keyboardType: TextInputType.text,
                        decoration: new InputDecoration(
                          border: InputBorder.none,
                          labelText: 'Message:',
                        ),
                      ),
                    ),
                    RaisedButton(
                      onPressed: _connected ? _writeTest : null,
                      child: Text('Send'),
                    ),
                  ],
                ),
              ),
              Padding(
                padding: const EdgeInsets.only(left: 10.0, right: 10.0),
                child: TextField(
                  controller: _text,
                  maxLines: null,
                  enabled: false,
                  decoration: new InputDecoration(
                    border: InputBorder.none,
                    labelText: 'Message:',
                  ),
                ),
              ),
            ],
          ),
        ),
              ],
            ),
          )
        ],
      ),
    );

    
  }
}
