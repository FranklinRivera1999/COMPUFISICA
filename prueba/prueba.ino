

#include <SFE_BMP180.h>
#include <Wire.h>  
#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

SFE_BMP180 pressure;

double PresionBase;
double Presion = 0;
double Altura = 0;
double Temperatura = 0;
char status;

void setup() {
  Serial.begin(9600);

  SensorStart();
} 

void loop() {
 ReadSensor();
 Serial.println("{\"H\":"+(String)dht.readHumidity()+", \"T\":"+(String)dht.readTemperature()+", \"P\":"+(String)Presion+", \"A\":"+(String)Altura+", \"T2\":"+(String)Temperatura+"}");
 delay(1000);
 
 
}


void SensorStart() {
//Secuencia de inicio del sensor
if (pressure.begin())
delay(100);
else
{
Serial.println("BMP180 init fail (disconnected?)\n\n");
while (1);
}
//Se inicia la lectura de temperatura
status = pressure.startTemperature();
if (status != 0) {
delay(status);
//Se lee una temperatura inicial
status = pressure.getTemperature(Temperatura);
if (status != 0) {
//Se inicia la lectura de presiones
status = pressure.startPressure(3);
if (status != 0) 
{
delay(status);
//Se lee la presión inicial incidente sobre el sensor en la primera ejecución
status = pressure.getPressure(PresionBase, Temperatura);
}
}
}
}



void ReadSensor() {
//En este método se hacen las lecturas de presión y temperatura y se calcula la altura
//Se inicia la lectura de temperatura
status = pressure.startTemperature();
if (status != 0)
{
delay(status);
//Se realiza la lectura de temperatura
status = pressure.getTemperature(Temperatura);
if (status != 0)
{
//Se inicia la lectura de presión
status = pressure.startPressure(3);
if (status != 0)
{
delay(status);
//Se lleva a cabo la lectura de presión,</span>
//considerando la temperatura que afecta el desempeño del sensor</span>
status = pressure.getPressure(Presion, Temperatura);
if (status != 0)
{
//Cálculo de la altura en base a la presión leída en el Setup
Altura = pressure.altitude(Presion, PresionBase);
}

}

}

}

}
