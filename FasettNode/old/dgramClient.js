
const PORT = 7002;
const BROADCAST_ADDR = '255.255.255.255';

const dgram = require('dgram');
const server = dgram.createSocket('udp4');

server.bind(()=> {
	server.setBroadcast(true);
	setInterval(sendMessage, 1000);
});

function sendMessage() {
    var message = new Buffer("Multicast message!");
	server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function () {
		console.log("Sent '" + message + "'");
	});
}