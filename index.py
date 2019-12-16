import serial
import json
from firebase import firebase

firebase = firebase.FirebaseApplication('https://estacionmet-7edb5.firebaseio.com/',None)

result = firebase.get('/prueba', None)
print(result)

PORT='/dev/ttyACM0'
arduino = serial.Serial(PORT,9600)

while True:
    #jsonRead= arduino.readline()
    #print(arduino.readline())
    try:
        jsonObject= json.loads(arduino.readline())
        print(jsonObject["x"])
        print('-------')
    except Exception:
        pass