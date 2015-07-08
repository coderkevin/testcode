var express = require('express');

var app = express();

app.get('/', function(req, res) {
  res.send('Hello from express!');
});

console.log("Listening on port 8080");

app.listen(8080);
