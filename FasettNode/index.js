var five = require('johnny-five');
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

	for (const input of [2]){

		// http://johnny-five.io/api/sensor/
		const sensor = new five.Sensor.Digital(input);

		sensor.on('change', (value) => {

			// scale 0-1023 to 0-127
			// let value = sensor.scaleTo(0,127);

			const data = '/d'+input+' '+value;

			console.log(data);

			io.emit('chat', { msg: data });

		});
	}

});