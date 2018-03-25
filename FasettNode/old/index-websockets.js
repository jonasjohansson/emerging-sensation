const osc = require('osc');
const app = require('express')();
const http = require('http').Server(app);
const io = require('socket.io')(http);

// https://www.npmjs.com/package/particle-io
http.listen(3000, () => {
	console.log('listening on *:3000');
});

board.on('ready', () => {
	for (const input of [2]) {
		// http://johnny-five.io/api/sensor/
		const sensor = new five.Sensor.Digital(input);

		sensor.on('change', value => {
			// Const msg = '/d'+input;
			// const msg = '/d'+input+' '+value;

			// io.emit('chat', { msg: msg }

			const msg = '/CubeX';

			console.log(msg, value);

			udpPort.send({
				address: msg,
				args: [
					{
						type: 'f',
						value
					}
				]
			});

			// Client.send(msg, value, function (){
			// client.kill();
			// });
		});
	}
});

