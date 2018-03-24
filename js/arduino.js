var five = require("johnny-five");
var board = new five.Board();

const inputs = ["A0"];//,"A1","A2","A3","A4","A5"];
const sensors = [];

board.on("ready", function() {

	for (const input in inputs){
		let sensor = new five.Sensor(input);
		sensor.on("change", function(value) {
			console.log(input, value);
		});
		sensors.push(sensor);
	}

});