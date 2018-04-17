const dgram = require('dgram'); 
const SerialPort = require('serialport');

const server = dgram.createSocket('udp4'); 

const PORT 				= 9000;
const BROADCAST_ADDR 	= '255.255.255.255';
const BAUDRATE 			= 152000;
const DEBUG				= false;

server.bind(function() {
	server.setBroadcast(true);
});

SerialPort.list(function (err, results){
	let portData = results.filter(data => data.manufacturer === 'Teensyduino')[0];
	let port = new SerialPort(portData.comName, {
		baudRate: BAUDRATE
	});
	port.on('readable', function () {
		let data = port.read();
		data = data.toString('utf8');
		data = data.trim();
		const message = new Buffer(data);
		sendMessage(message);
	});
	port.on('error', function(err) {
		console.log('Error: ', err.message);
	})
});

if (DEBUG){
	let val = 0;
	setInterval(()=>{
		val = (val === '0') ? '127' : '0';
		const message = new Buffer(val);
		sendMessage(message);
	},1000);
}

function sendMessage(msg){
	server.send(msg, 0, msg.length, PORT, BROADCAST_ADDR, function() {
		console.log("Sent '" + msg + "'");
	});
}