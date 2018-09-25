const dgram = require('dgram'); 
const SerialPort = require('serialport');
const server = dgram.createSocket('udp4'); 

const PORT = 7003;
const BROADCAST_ADDR = '255.255.255.255';
const BAUDRATE = 152000;
const DEBUG = true;
const START = Date.now();

const devices = [
    {
        serialNumber: '2211820',
        id: 'a',
    },
    {
        serialNumber: '2214590',
        id: 'b',
    }
]

server.bind(function() {
    server.setBroadcast(true);
});

async function getPort() {
    let ports = await getPorts();
    ports = ports.filter(data => data.manufacturer === 'Teensyduino');
    if (ports.length > 0){
        for (let port of ports){
            setId(port);
            connectPort(port.comName,port.id);
        }
    } else {
        setTimeout(getPort,3000);
    }
}

async function getPorts() {
    console.log('Scanning all ports…');
    return SerialPort.list();
}

function setId(port){
    for (var key in devices){
        let device = devices[key];
        if (device.serialNumber === port.serialNumber){
            port.id = device.id;
        }
    }
}

function connectPort(com,id){
    console.log('Connecting to port:',com);
    let port = new SerialPort(com, {
        baudRate: BAUDRATE
    });
    port.on('readable', function () {
        let msg = getMessage(port);
        sprayMessage(id+msg);
        // sendMessage(id+msg);
    });
    port.on('open', function(err) {
        console.log('Port connected!');
        port.startSending();
        reset();
    });
    port.on('close', function(err) {
        console.log('Port closed!');
        console.log('Reconnecting…')
        getPort();
    });
}

getMessage = (port) => {
    let data = port.read();
    data = data.toString('utf8');
    data = data.trim();
    return new Buffer(data);
}

sendMessage = (message) => {
    server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function() {
        console.log(`Sent ${message}`);
    });
}

sprayMessage = (message) => {
    for (let i = 0; i < 10; i++){
        setTimeout(()=>{
        	sendMessage(message);
        },i*20);
    }
}

reset = () => {
    for (let i = 0; i < 12; i++){
        sendMessage('a'+i+' 0');
        sendMessage('b'+i+' 0');
    }
}

ping = () => {
    let timeElapsed = Date.now() - START;
    sendMessage(`Ping! ${timeElapsed}ms has passed since start.`)
}

getPort();

setInterval(ping, 4000);

if (DEBUG){
	let val;
	setInterval(()=>{
		val = (val == '0') ? '1' : '0';
		const msg = new Buffer(val);
	    for (let i = 0; i < 12; i++){
	        sprayMessage(`a${i} ${val}`);
	        sprayMessage(`b${i} ${val}`);
	    }
	},4000);
}