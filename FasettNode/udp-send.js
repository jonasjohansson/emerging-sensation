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

async function getPort() {
	let ports = await getPorts();
	let port = ports.filter(data => data.manufacturer === 'Teensyduino')[0];
	if (port !== undefined){
		connectPort(port.comName);
	} else {
		setTimeout(getPort,3000);
	}
}

async function getPorts() {
	console.log('Scanning all ports…');
	return SerialPort.list();
}

function connectPort(com){
	console.log('Connecting to port:',com);
	let port = new SerialPort(com, {
		baudRate: BAUDRATE
	});
	port.on('readable', function () {
		readData(port);
	});
	port.on('open', function(err) {
		connected = true;
		console.log('Port connected!');
	});
	port.on('close', function(err) {
		console.log('Port closed!');
		console.log('Reconnecting…')
		getPort();
	});
}

function readData(port){
	let data = port.read();
	data = data.toString('utf8');
	data = data.trim();
	const message = new Buffer(data);
	sendMessage(message);
}

function sendMessage(msg){
	server.send(msg, 0, msg.length, PORT, BROADCAST_ADDR, function() {
		console.log("Sent '" + msg + "'");
	});
}

getPort();

if (DEBUG){
	let val = 0;
	setInterval(()=>{
		val = (val === '0') ? '127' : '0';
		const message = new Buffer(val);
		sendMessage(message);
	},1000);
}