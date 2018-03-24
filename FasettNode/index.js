// https://github.com/alexanderwallin/harpaio-music-engine/blob/master/src/resolume-osc.js
var five = require('johnny-five');
var osc = require('osc');
// var app = require('express')();
// var http = require('http').Server(app);
// var io = require('socket.io')(http);

// https://socket.io/
// http.listen(3000, function(){
// 	console.log('listening on *:3000');
// });

const udpPort = new osc.UDPPort({
    broadcast: true,
    localAddress: "0.0.0.0",
    localPort: 57122,
    remoteAddress: "255.255.255.255",
    remotePort: 57121
});

udpPort.open();

// http://johnny-five.io/api/board/
const board = new five.Board({
	port: '/dev/cu.usbmodem1411',
	repl: false,
	debug: false
});

board.on('ready', function() {

	for (const input of [2]){

		// http://johnny-five.io/api/sensor/
		const sensor = new five.Sensor.Digital(input);

		sensor.on('change', (value) => {

			// const msg = '/d'+input;
			// const msg = '/d'+input+' '+value;

			// io.emit('chat', { msg: msg }
			
			const msg = '/CubeX';

			console.log(msg,value);

			udpPort.send({
				address: msg,
				args: [
					{
						type: 'f',
						value: value
					}
				]
			});

			// client.send(msg, value, function (){
				// client.kill();
			// });
		});
	}
});



