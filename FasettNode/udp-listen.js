var PORT = 7002;
var dgram = require('dgram');
var socket = dgram.createSocket('udp4');

socket.on('listening', function () {
    var address = socket.address();
    console.log('UDP Client listening on ' + address.address + ":" + address.port);
    socket.setBroadcast(true);
});

socket.on('message', function (message, rinfo) {
    console.log('Message from: ' + rinfo.address + ':' + rinfo.port +' - ' + message);
});

socket.bind(PORT);