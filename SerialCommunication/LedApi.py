from flask import Flask, request
from flask_restful import Api, Resource, reqparse

import time
import serial
import os

import json

app = Flask(__name__)
api = Api(app)

ser = None



currentConfig = {
    "isRainbow": False,
    "isSolid": False,
    "rgb": [255, 255, 255],
    "speed": 0.01,
    "strength": 1,
    "angularSpeed": 1 
    }

ser = serial.Serial('COM3', 9600)
#need to delay the start while arduino gets set up becase it restarts when serial connects.
time.sleep(5);

    
def arduinoString(config):
    output = "r" + str(1 if config["isRainbow"] else 0)
    output += "s" + str(1 if config["isSolid"] else 0)
    output += "S" + str(config["speed"])
    output += "R" + str(config["rgb"][0])
    output += "G" + str(config["rgb"][1])
    output += "B" + str(config["rgb"][2])
    output += "b" + str(config["strength"])
    output += "a" + str(config["angularSpeed"])

    return output

class LightConfig(Resource):

    def get(self):
        return arduinoString(currentConfig), 200

    def post(self):
        req_data = request.get_data()

        currentConfig = json.loads(req_data)
        command = arduinoString(currentConfig)
        ser.write(command.encode())
        return 200


  
try:
    api.add_resource(LightConfig, "/lightconfig")
    app.run(debug=True, use_reloader=False)

finally:
    ser.close()
