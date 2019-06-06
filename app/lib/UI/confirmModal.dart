import 'package:flutter/material.dart';

class ConfirmModal extends StatelessWidget {
  const ConfirmModal({Key key, this.valid}) : super(key: key);
  final bool valid;
  @override
  Widget build(BuildContext context) {
    print(valid);
    return Scaffold(
      backgroundColor: Colors.black.withOpacity(0.85),
      body: InkWell(
        onTap: () {
          Navigator.of(context).pop();
        },
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
          
              valid == true
                  ? Icon(
                      Icons.check_circle,
                      color: Colors.white,
                      size: 60,
                    )
                  : Icon(
                      Icons.cancel,
                      color: Colors.white,
                      size: 60,
                    ),
              SizedBox(
                height: 15,
              ),
              valid == true
                  ? Text('Confirmed, Pouring Drink',
                      style: TextStyle(
                        color: Colors.white,
                        fontSize: 30,
                      ))
                  : Text(
                      'Not of Age',
                      style: TextStyle(
                        color: Colors.white,
                        fontSize: 30,
                      ),
                    ),
            ],
          ),
        ),
      ),
    );
  }
}
