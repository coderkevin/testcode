var express = require('express');

var app = express();

app.get('/', function(req, res) {
  res.send('Hello from express!');
});

app.listen(8080);
