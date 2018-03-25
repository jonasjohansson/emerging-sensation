var osc = require('osc');

const udpPort = new osc.UDPPort({
    localAddress: "0.0.0.0",
    localPort: 57121,
});

udpPort.open();

udpPort.on("message", function (oscMsg) {
	console.log(oscMsg);
});