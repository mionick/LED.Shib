var LedConfiguration = require("../models/ledconfiguration");

SerialPort = require('serialport');
//SERIAL
var portName = 'COM3'; // '/dev/ttyACM0';
var sp = new SerialPort(portName, 
{ // portName is instatiated to be COM3, replace as necessary
   baudRate: 9600, // this is synced to what was set for the Arduino Code
   dataBits: 8, // this is the default for Arduino serial communication
   parity: 'none', // this is the default for Arduino serial communication
   stopBits: 1, // this is the default for Arduino serial communication
   flowControl: false // this is the default for Arduino serial communication
});


var currentConfig = new LedConfiguration();

exports.getCurrentConfig = function(req, res) {
    console.log(LedConfiguration);
    res.json(currentConfig);
}   

exports.pushConfig = function(req, res) {
    currentConfig = new LedConfiguration(
        req.body.rgb,
        req.body.isRainbow,
        req.body.isSolid,
        req.body.strength,
        req.body.speed,
        req.body.angularSpeed
    );
    console.log( req.body);
    sp.write(currentConfig.toArduinoString());

    res.json(currentConfig);
}