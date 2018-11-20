const dgram = require('dgram');
const SerialPort = require('serialport');
const server = dgram.createSocket('udp4');

const PORT = 7003;
const BROADCAST_ADDR = '255.255.255.255';
const BAUDRATE = 152000;
const DEBUG = false;
const START = Date.now();

const devices = [
    {
        serialNumber: '2211820',
        id: 'a'
    },
    {
        serialNumber: '4655120',
        id: 'b'
    }
];

server.bind(function() {
    server.setBroadcast(true);
});

async function getPort() {
    let ports = await getPorts();
    ports = ports.filter(data => data.manufacturer === 'Teensyduino');
    if (ports.length > 0) {
        for (let port of ports) {
            setId(port);
            connectPort(port.comName, port.id);
        }
    } else {
        setTimeout(getPort, 3000);
    }
}

async function getPorts() {
    console.log('Scanning all ports…');
    return SerialPort.list();
}

function setId(port) {
    for (var key in devices) {
        let device = devices[key];
        if (device.serialNumber === port.serialNumber) {
            port.id = device.id;
        }
    }
}

function connectPort(com, id) {
    console.log('Connecting to port:', com);

    let port = new SerialPort(com, {
        baudRate: BAUDRATE,
        parser: SerialPort.parsers.raw
    });

    let Readline = SerialPort.parsers.Readline;
    let parser = new Readline();
    port.pipe(parser);

    parser.on('data', function(data) {
        // console.log('data received: ' + data);
        console.log(`${id} ${data}`);
    });

    port.on('open', () => {
        console.log('port open');
    });

    port.on('readable', () => {
        // console.log('reading…');
        // console.log('Data:', port.read());
        var buffer = port.read();
        if (buffer !== null) {
            msg = buffer.toString('utf8');
            msg = msg.trim();
            // console.log(msg);
            // sendMessage(`${id} ${msg}`);
        }
    });
    port.on('close', function(err) {
        console.log('Port closed!');
        console.log('Reconnecting…');
        getPort();
    });
    port.on('error', function(err) {
        console.log('Error: ', err.message);
    });
}

sendMessage = message => {
    console.log(message);
    server.send(message, 0, message.length, PORT, BROADCAST_ADDR, function() {
        // console.log(`Sent ${message}`);
    });
};

sprayMessage = message => {
    for (let i = 0; i < 10; i++) {
        setTimeout(() => {
            sendMessage(message);
        }, i * 20);
    }
};

getPort();
