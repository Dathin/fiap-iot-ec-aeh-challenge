const WebSocket = require('ws');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const server = new WebSocket.Server({
  port: 8004
});


const sockets = [];

server.on('connection', socket => {
	console.log('got a connection:');
	sockets.push(socket);	
});

const port = new SerialPort('/dev/tnt1', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
parser.on('data', data =>{
  sockets.forEach(socket => socket.send(data));
});
