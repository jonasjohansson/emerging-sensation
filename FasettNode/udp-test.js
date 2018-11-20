const dgram = require('dgram');
const server = dgram.createSocket('udp4');

const PORT = 7003;
const BROADCAST_ADDR = '255.255.255.255';
const BAUDRATE = 152000;

server.bind(function() {
	server.setBroadcast(true);
});

sendMessage = message => {
	server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function() {
		console.log(`Sent ${message}`);
	});
};

sprayMessage = message => {
	for (let i = 0; i < 10; i++) {
		setTimeout(() => {
			sendMessage(message);
		}, i * 20);
	}
};

reset = () => {
	for (let i = 0; i < 12; i++) {
		sendMessage('a' + i + ' 0');
		sendMessage('b' + i + ' 0');
	}
};

setInterval(() => {
	sprayMessage('b0 0.4');
	setTimeout(() => {
		sprayMessage('b0 0.8');
	}, 1000);
}, 2000);
