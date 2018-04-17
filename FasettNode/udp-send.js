/*

- smarter reconenct with n devices available
- more efficient lookup for device id

*/

const dgram = require('dgram'); 
const SerialPort = require('serialport');

const server = dgram.createSocket('udp4'); 

const PORT 				= 9000;
const BROADCAST_ADDR 	= '255.255.255.255';
const BAUDRATE 			= 152000;

const devices = [
	{
		serialNumber: '2211820',
		id: 'a',
	},
	{
		serialNumber: '2214590',
		id: 'b',
	}
]

server.bind(function() {
	server.setBroadcast(true);
});

async function getPort() {
	let ports = await getPorts();
	ports = ports.filter(data => data.manufacturer === 'Teensyduino');
	if (ports.length > 0){
		for (let port of ports){
			setId(port);
			connectPort(port.comName,port.id);
		}
	} else {
		setTimeout(getPort,3000);
	}
}

function setId(port){
	for (var key in devices){
		let device = devices[key];
		if (device.serialNumber === port.serialNumber){
			port.id = device.id;
		}
	}
}

async function getPorts() {
	console.log('Scanning all ports…');
	return SerialPort.list();
}

function connectPort(com,id){
	console.log('Connecting to port:',com);
	let port = new SerialPort(com, {
		baudRate: BAUDRATE
	});
	port.on('readable', function () {
		let msg = getMessage(port);
		sendMessage(id+msg);
	});
	port.on('open', function(err) {
		console.log('Port connected!');
	});
	port.on('close', function(err) {
		console.log('Port closed!');
		console.log('Reconnecting…')
		getPort();
	});
}

function getMessage(port){
	let data = port.read();
	data = data.toString('utf8');
	data = data.trim();
	return new Buffer(data);
}

function sendMessage(msg){
	server.send(msg, 0, msg.length, PORT, BROADCAST_ADDR, function() {
		console.log("Sent '" + msg + "'");
	});
}

getPort();