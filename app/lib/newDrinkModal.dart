import 'package:flutter/material.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

class AddNewDrink extends StatefulWidget {
  AddNewDrink({Key key, this.data}) : super(key: key);
  final String data;
  @override
  State<StatefulWidget> createState() {
    return AddNewDrinkState();
  }
}

class AddNewDrinkState extends State<AddNewDrink> {
  final _formKey = GlobalKey<FormState>();
  Firestore db = Firestore.instance;
  bool isSwitched = false;
  final TextEditingController _drinkName = TextEditingController();
  List<String> _colors = <String>[
    '',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9'
  ];
  String _drink1 = '';
  String _drink2 = '';
  String _drink3 = '';

  // -------- WORK DONE BY SAUL -----------------
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Add A Drink')),
      body: SingleChildScrollView(
        child: Column(
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
                      controller: _drinkName,
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
                        if (_drink1 == '' || _drink1 == null) {
                          return 'Please choose drinks';
                        }
                      },
                      builder: (FormFieldState state) {
                        return InputDecorator(
                          decoration: InputDecoration(
                            labelText: 'Drink Selector 1',
                          ),
                          isEmpty: _drink1 == '',
                          child: DropdownButtonHideUnderline(
                            child: DropdownButton(
                              value: _drink1,
                              isDense: true,
                              onChanged: (String newValue) {
                                setState(() {
                                  _drink1 = newValue;
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
                    padding: const EdgeInsets.symmetric(horizontal: 50.0),
                    child: FormField(
                      validator: (value) {
                        if (_drink2 == '' || _drink2 == null) {
                          return 'Please choose drinks';
                        }
                      },
                      builder: (FormFieldState state) {
                        return InputDecorator(
                          decoration: InputDecoration(
                            labelText: 'Drink Selector 2',
                          ),
                          isEmpty: _drink2 == '',
                          child: DropdownButtonHideUnderline(
                            child: DropdownButton(
                              value: _drink2,
                              isDense: true,
                              onChanged: (String newValue) {
                                setState(() {
                                  _drink2 = newValue;
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
                    padding: const EdgeInsets.symmetric(horizontal: 50.0),
                    child: FormField(
                      validator: (value) {
                        if (_drink3 == '' || _drink3 == null) {
                          return 'Please choose drinks';
                        }
                      },
                      builder: (FormFieldState state) {
                        return InputDecorator(
                          decoration: InputDecoration(
                            labelText: 'Drink Selector 3',
                          ),
                          isEmpty: _drink3 == '',
                          child: DropdownButtonHideUnderline(
                            child: DropdownButton(
                              value: _drink3,
                              isDense: true,
                              onChanged: (String newValue) {
                                setState(() {
                                  _drink3 = newValue;
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
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: <Widget>[
                        Text('Age Restrict'),
                        Switch(
                          onChanged: (value) {
                            setState(() {
                              isSwitched = value;
                            });
                          },
                          value: isSwitched,
                          activeColor: Colors.blue,
                          activeTrackColor: Colors.lightBlueAccent,
                        )
                      ],
                    ),
                  ),
                  Padding(
                    padding: const EdgeInsets.symmetric(vertical: 16.0),
                    child: RaisedButton(
                      onPressed: () {
                        // Validate will return true if the form is valid, or false if
                        // the form is invalid.
                        if (_formKey.currentState.validate()) {
                          String drinkOz = _drink1 + _drink2 + _drink3;
                          var data = {
                            'title': _drinkName.text,
                            'createdAt': DateTime.now(),
                            'uid': 'aaa',
                            'tag': drinkOz,
                            'total': int.parse(_drink1) +
                                int.parse(_drink2) +
                                int.parse(_drink3),
                            'restrict': isSwitched
                          };
                          db.collection('drinks').add(data);
                          Navigator.pop(context);
                          // If the form is valid, we want to show a Snackbar

                        }
                      },
                      child: Text('Submit'),
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }
}

// ------- END WORK DONE BY SAUL
