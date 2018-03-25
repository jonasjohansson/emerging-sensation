const osc = require('osc');

const udpPort = new osc.UDPPort({
	localAddress: '0.0.0.0',
	localPort: 7002
});

udpPort.open();

udpPort.on('message', oscMsg => {
	console.log(oscMsg);
});
