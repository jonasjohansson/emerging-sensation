const dgram = require("dgram");
const SerialPort = require("serialport");
const server = dgram.createSocket("udp4");

const PORT = 7003;
const BROADCAST_ADDR = "255.255.255.255";
const BAUDRATE = 152000;
const RECONNECT_DELAY = 200;

server.bind(function() {
	server.setBroadcast(true);
});

async function getPort() {
	let ports = await getPorts();
	console.log(ports);
	ports = ports.filter(data => data.manufacturer === "Teensyduino");
	if (ports.length > 0) {
		for (let port of ports) {
			connectPort(port.comName);
		}
	} else {
		setTimeout(getPort, 3000);
	}
}

async function getPorts() {
	console.log("Scanning all USB ports…");
	return SerialPort.list();
}

function connectPort(com) {
	console.log("Connecting port", com);

	let port = new SerialPort(com, {
		baudRate: BAUDRATE,
		parser: SerialPort.parsers.raw,
		autoStart: false,
		lock: true
	});

	let Readline = SerialPort.parsers.Readline;
	let parser = new Readline();
	port.pipe(parser);

	parser.on("data", function(data) {
		sprayMessage(data);
	});

	port.on("open", () => {
		console.log(com, "open! Let there be light!");
	});

	port.on("close", function(err) {
		console.log("Port", com, "closed! Reconnecting…");
		setTimeout(function() {
			connectPort(com);
		}, RECONNECT_DELAY);
	});

	port.on("error", function(err) {
		console.log("Error: ", err.message);
	});

	setTimeout(function() {
		port.open();
	}, 500);
}

function sendMessage(message) {
	server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function() {});
}

function sprayMessage(message) {
	console.log(message);
	for (let i = 0; i < 5; i++) {
		setTimeout(() => {
			sendMessage(message);
		}, i * 40);
	}
}

getPort();
