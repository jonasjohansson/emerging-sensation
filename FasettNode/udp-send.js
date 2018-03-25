const dgram = require('dgram'); 
const SerialPort = require('serialport');

var PORT = 7003;
var BROADCAST_ADDR = "255.255.255.255";
var server = dgram.createSocket("udp4"); 

server.bind(function() {
    server.setBroadcast(true);
});

// const port = new SerialPort('/dev/cu.usbmodem1411', {
// 	baudRate: 9600,
// });

const port = new SerialPort('/dev/cu.usbmodem2211821', {
	baudRate: 152000
});

port.on('readable', function () {
	let data = port.read();
	// console.log('Data:', data);
    data = data.toString('utf8');
    data = data.trim();
	const message = new Buffer(data);
    server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function() {
        console.log("Sent '" + message + "'");
    });
});