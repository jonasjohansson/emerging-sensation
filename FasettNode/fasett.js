// https://github.com/russellmcc/node-osc-min
// https://github.com/alexanderwallin/harpaio-music-engine/blob/master/src/resolume-osc.js
var osc = require('node-osc');
var five = require("johnny-five");
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

// https://socket.io/
http.listen(3000, function(){
	console.log('listening on *:3000');
});

// http://johnny-five.io/api/board/
const board = new five.Board({
	port: '/dev/cu.usbmodem1411',
	repl: false,
	debug: false
});

board.on('ready', function() {

	const client = new osc.Client('127.0.0.1', 6969);

	for (const input of [2]){

		// http://johnny-five.io/api/sensor/
		const sensor = new five.Sensor.Digital(input);

		sensor.on('change', (value) => {

			// scale 0-1023 to 0-127
			// let value = sensor.scaleTo(0,127);

			const msg = '/d'+input;

			console.log(msg, value);

			// client.send(msg, value, function (){
			// 	client.kill();
			// });

			io.on('connection', (socket) => {
				io.emit('chat', { msg: msg });
			});

		});
	}

});