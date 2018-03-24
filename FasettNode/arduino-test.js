var five = require("johnny-five");
var board = new five.Board();

const analogInputs = ["A0","A1","A2","A3","A4","A5"];
const sensors = [];

board.on("ready", function() {

	let sensor = new five.Sensor()
	for (const analogInput in analogInputs){
		let sensor = new five.Sensor(analogInput);
		sensor.on("change", function(value) {
			console.log(analogInput, value);
		});
		sensors.push(sensor);
	}

});