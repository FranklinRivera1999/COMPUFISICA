

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

int encoder_pin = 2;         
unsigned int rpm = 0;    
float velocity = 0;     
volatile byte pulses = 0;    
unsigned long timeold = 0;
unsigned long timecurrent = 0;  
unsigned int pulsesperturn = 20; 
const int wheel_diameter = 64;   
static volatile unsigned long debounce = 0; 


void setup() {
  Serial.begin(9600);

  SensorStart();
  pinMode(encoder_pin, INPUT);
   attachInterrupt(0, counter, RISING);
   pulses = 0;
   rpm = 0;
   timeold = 0;
   timecurrent=0;
} 

void loop() {

 if (millis() - timeold >= 1000){ 
      noInterrupts();
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses; 
      velocity = rpm * 3.1416 * wheel_diameter * 60 / 1000000;
      timeold = millis(); 
      timecurrent=millis()/1000;
      pulses = 0; 
      interrupts();
 }
 ReadSensor();
 Serial.println("{\"H\":"+(String)dht.readHumidity()+", \"T\":"+(String)dht.readTemperature()+", \"P\":"
 +(String)Presion+", \"A\":"+(String)Altura+", \"T2\":"+(String)Temperatura+", \"V\":"+(String)velocity+", \"Time\":"+(String)timecurrent+"}");
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


void counter(){
  if(  digitalRead (encoder_pin) && (micros()-debounce > 500) && digitalRead (encoder_pin) ) { 
        debounce = micros(); 
        pulses++;}  
        else ; } 
