const SerialPort = require('serialport');
const osc = require('osc');

const udpPort = new osc.UDPPort({
	broadcast: true,
	localAddress: '0.0.0.0',
	localPort: 57122,
	remoteAddress: '255.255.255.255',
	remotePort: 57121
});

udpPort.open();

const port = new SerialPort('/dev/cu.usbmodem1411', {
	baudRate: 9600
});

// Const port = new SerialPort('/dev/cu.usbmodem2214591', {
// 	baudRate: 152000
// });

port.on('readable', () => {
	const val = port.read();

	const msg = '/d0';

	console.log(msg, val[1]);

	// https://github.com/node-serialport/node-serialport/issues/1069
	udpPort.send({
		address: msg,
		args: [
			{
				type: 'i',
				value: val[1]
			}
		]
	});
});
