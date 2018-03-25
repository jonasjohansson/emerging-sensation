var osc = require('osc');

const udpPort = new osc.UDPPort({
    broadcast: true,
    localAddress: "0.0.0.0",
    localPort: 57122,
    remoteAddress: "255.255.255.255",
    remotePort: 57121
});

udpPort.open();

let val = 0;

function sendMsg(){

	setTimeout(()=>{

		val = (val == 0) ? 1 : 0

		udpPort.send({
			address: '/d0',
			args: [
				{
					type: 'f',
					value: val
				}
			]
		});

		console.log('sending',val);
	
		sendMsg();

	},1000);
}

sendMsg();