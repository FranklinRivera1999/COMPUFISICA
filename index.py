import serial
import json
from firebase import firebase
import requests


firebase = firebase.FirebaseApplication('https://estacionmet-7edb5.firebaseio.com/',None)

result = firebase.get('/prueba', None)
print(result)
print('declarando ARDUINO UNO')
PORT='/dev/ttyACM0'
arduino = serial.Serial(PORT,9600)


while True:
    #jsonRead= arduino.readline()
    #print(arduino.readline())
    try:
        jsonObject= json.loads(arduino.readline())
        print(jsonObject["H"])
        print(jsonObject["T"])
        print(jsonObject["P"])
        print(jsonObject["A"])
        print(jsonObject["T2"])
        print(jsonObject["V"])
        print(jsonObject["Time"])
        print('-------')
    except Exception:
        pass