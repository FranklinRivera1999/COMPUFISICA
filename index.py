import serial
import json
import requests


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
        print(jsonObject["L"])
        print(type(jsonObject["Time"]))
        print('-------enviar thingsspeak-----')
        enviar = requests.get("https://api.thingspeak.com/update?api_key=3HIK3GQGLHPDWYWV&field1="
        + str(jsonObject["T"]) + "&field2=" + str(jsonObject["H"]) + "&field3=" + str(jsonObject["P"]) + "&field4=" + str(jsonObject["A"]))
        print('Columnas Enviadas')

    except Exception:
        pass