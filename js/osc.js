var osc = require('node-osc');

var client = new osc.Client('127.0.0.1', 6969);
client.send('/CubeX', 10, function () {
	client.kill();
});