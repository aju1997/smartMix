import 'package:flutter/material.dart';

// ---------- DONE BY SAUL -------------------
class DrinkCard extends StatelessWidget {
  final String url;
  final String title;
  DrinkCard({Key key, this.title, this.url}) : super(key: key);
  @override
  Widget build(BuildContext context) {
    return Card(
      shape: BeveledRectangleBorder(borderRadius: BorderRadius.circular(20)),
      child: Container(
        width: 150,
        height: 200,
        decoration: BoxDecoration(
          borderRadius: BorderRadius.circular(20),
          boxShadow: [
            BoxShadow(
                color: Colors.black87, blurRadius: 4, offset: Offset(0, 0))
          ],
          image: DecorationImage(
              fit: BoxFit.cover,
              image: NetworkImage(
                'https://static.independent.co.uk/s3fs-public/thumbnails/image/2018/05/22/13/gin-cocktails.jpg?w968h681',
              )),
        ),
        child: Center(
          child: SingleChildScrollView(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.start,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                SizedBox(
                  height: 75,
                ),
                Text(
                  title,
                  style: TextStyle(
                      color: Colors.white,
                      fontWeight: FontWeight.w700,
                      fontSize: 25),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
// ----------- END OF WORK DONE BY SAUL
