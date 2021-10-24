const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const mqtt = require('mqtt');

const port = new SerialPort('/dev/tnt1', { baudRate: 9600 });

const parser = port.pipe(new Readline({ delimiter: '\n' }));

//initialize the MQTT client
const mqttClient = mqtt.connect({
  host: '73c9b9e3ef304ef1975e487d39a8be59.s1.eu.hivemq.cloud',
  port: 8883,
  protocol: 'mqtts',
  username: 'melindroso',
  password: 'Melindroso20'
});

mqttClient.on('connect', () => console.log('Connected'));

parser.on('data', data => {
  console.log(data);
  const parsedData = JSON.parse(data)
  if(parsedData.emergency){
    mqttClient.publish('emergency', data);
  } else {
    mqttClient.publish('vital_signs', data);
  }
  
});
