import 'package:flutter/material.dart';

class AddNewDrink extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return AddNewDrinkState();
  }
}

class AddNewDrinkState extends State<AddNewDrink> {
  final _formKey = GlobalKey<FormState>();
  List<String> _colors = <String>['', 'red', 'green', 'blue', 'orange'];
  String _color = '';

  // -------- WORK DONE BY SAUL -----------------
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
              ],
            ),
          )
        ],
      ),
    );
  }
}

// ------- END WORK DONE BY SAUL
