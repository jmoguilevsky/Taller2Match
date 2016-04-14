var pg = require('pg');
var cool = require('cool-ascii-faces');
var express = require('express');
var bodyParser  = require("body-parser"),
var methodOverride = require("method-override");
var app = express();
var server   = http.createServer(app)

/*
var conString = "postgres://YourUserName:YourPassword@localhost:5432/YourDatabase";
var client = new pg.Client(conString);
client.connect();
*/

app.use(bodyParser.urlencoded({ extended: false }));  
app.use(bodyParser.json());  
app.use(methodOverride());

app.set('port', (process.env.PORT || 5000));

app.use(express.static(__dirname + '/public'));

// views is directory for all template files
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');

app.get('/', function(request, response) {
  response.send(process.env.DATABASE_URL);
});

app.get('/cool2', function(request, response) {
  response.send(cool());
});

app.get('/db', function (request, response) {
    pg.defaults.ssl = true;
    pg.connect(process.env.DATABASE_URL, function(err, client, done) {
    client.query('SELECT * FROM usuario', function(err, result) {
      done();
      if (err)
       { console.error(err); response.send("Error " + err); }
      else
       { response.render('pages/db', {results: result.rows} ); }
    });
  });
})

app.listen(app.get('port'), function() {
  console.log('Node app is running on port', app.get('port'));
});


var router = express.Router();

router.get('/', function(req, res) {  
   res.send("Hello World!");
});

app.use(router);

exports.findAllUsers = function (request, response) {
  // body...
}