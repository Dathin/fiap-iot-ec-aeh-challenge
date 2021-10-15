const WebSocket = require('ws');

const client = new WebSocket('ws://localhost:8004')
client.on('message', msg => console.log(JSON.parse(msg)));
