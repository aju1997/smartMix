import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'smartMix',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'smartMix'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
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
            onTap: () {},
          ),
          ListTile(
            title: Text('Create Mix'),
            leading: Icon(Icons.list),
            onTap: () {},
          ),
          ListTile(
            title: Text('All Drinks'),
            leading: Icon(Icons.star),
            onTap: () {},
          ),
        ]),
      ),
      body: SingleChildScrollView(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Padding(
              padding: EdgeInsets.all(15.0),
              child: Text(
                'Most Used Mix',
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30,
                ),
              ),
            ),
            Padding(
              padding: EdgeInsets.all(10.0),
              child: Card(
                shape: BeveledRectangleBorder(
                    borderRadius: BorderRadius.circular(20)),
                child: Container(
                  width: MediaQuery.of(context).size.width,
                  height: MediaQuery.of(context).size.width / 2,
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(20),
                    boxShadow: [
                      BoxShadow(
                          color: Colors.black87,
                          blurRadius: 10,
                          offset: Offset(0, 0))
                    ],
                    image: DecorationImage(
                        fit: BoxFit.cover,
                        image: NetworkImage(
                          'https://static.independent.co.uk/s3fs-public/thumbnails/image/2018/05/22/13/gin-cocktails.jpg?w968h681',
                        )),
                  ),
                ),
              ),
            ),
            Padding(
              padding: EdgeInsets.all(15.0),
              child: Text(
                'Selection',
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30,
                ),
              ),
            ),
            Container(
              height: 200,
              width: MediaQuery.of(context).size.width,
              child: ListView(
                scrollDirection: Axis.horizontal,
                children: <Widget>[
                  drinkCard('Coke'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Coke'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Coke'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Coke'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Coke'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Coke'),
                ],
              ),
            ),
            Padding(
              padding: EdgeInsets.all(15.0),
              child: Text(
                'Custom',
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30,
                ),
              ),
            ),
            Container(
              height: 200,
              width: MediaQuery.of(context).size.width,
              child: ListView(
                scrollDirection: Axis.horizontal,
                children: <Widget>[
                  drinkCard('Drink Name'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Drink Name'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Drink Name'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Drink Name'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Drink Name'),
                  SizedBox(
                    width: 5,
                  ),
                  drinkCard('Drink Name'),
                ],
              ),
            ),
            SizedBox(
              height: 15,
            ),
          ],
        ),
      ),
    );
  }

  Widget drinkCard(String title, {url}) {
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
