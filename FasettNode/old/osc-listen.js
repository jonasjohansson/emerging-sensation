const osc = require('osc');

const udpPort = new osc.UDPPort({
	localAddress: '0.0.0.0',
	localPort: 9000
});

udpPort.open();

udpPort.on('message', oscMsg => {
	console.log(oscMsg);
});
