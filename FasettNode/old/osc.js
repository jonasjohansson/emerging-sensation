const dgram = require('dgram');
const osc = require('osc-min');

const SRC_PORT = 7001;
const OSC_PORT = 7002;
const MULTICAST_ADDR = '255.255.255.255';

// https://stackoverflow.com/questions/6177423/send-broadcast-datagram
const socket = dgram.createSocket('udp4');

socket.bind(SRC_PORT, ()=> {
	socket.setBroadcast(true);
})

socket.on('error', err => {
	console.log('Error:');
	console.log(err);
	console.log(err.stack);
});

function sendValue(address, value) {
	return new Promise((resolve, reject) => {
		const message = osc.toBuffer({
			address,
			args: [value]
		});
		console.log(message);
		socket.send(message, 0, message.length, OSC_PORT, MULTICAST_ADDR, err => {
			if (err) {
				reject(err);
			} else {
				resolve();
			}
		});
	});
}

module.exports.sendValue = sendValue;
