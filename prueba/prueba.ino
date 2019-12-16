

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  
 Serial.println("{\"x\":"+(String)analogRead(sensorPin)+"}");
 delay(1000);
}
