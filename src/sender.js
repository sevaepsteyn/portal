var dgram = require('dgram');

var HOST = '127.0.0.1';
var PORT = 7979;

var message = '0,0,0'; // default, if nothing is specified on cli
if(process.argv.length == 3) message = process.argv[2]; // first is nodejs, second is app)
var buffer = Buffer.from(message);

var client = dgram.createSocket('udp4');
client.send(buffer, 0, message.length, PORT, HOST, function(err, bytes) {
  if (err) throw err;
  console.log('UDP message(' + message + ') sent to ' + HOST +':'+ PORT);
  client.close();
});
