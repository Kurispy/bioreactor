#include <math.h>

int diodePin = A0;    // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int switchPin = 9;    //Switch toggles calibration mode
int diodeSensorValue = 0;  // variable to store the value coming from the sensor
int lightOnAvg = 0;
int lightOffAvg = 0;
int diodeReading = 0;
int diff = 0;
int ODZero = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);
  analogReadResolution(12);
}

void loop() {
  if(Serial.available())
  {
    Serial.read();
    Serial.print("Calibrating...\n");
    ODZero = 0;
    digitalWrite(ledPin, LOW);
    for(int i = 0; i < 10; i++)
    {
      diodeSensorValue = 0;
      for (int j = 0; j < 30; j++) {
        diodeSensorValue += analogRead(diodePin);
        delay(10);
      }
      lightOffAvg = diodeSensorValue / 30;
      digitalWrite(ledPin, HIGH);
      delayMicroseconds(1);
      diodeSensorValue = 0;
      for (int j = 0; j < 30; j++) {
        diodeSensorValue += analogRead(diodePin);
        delay(10);
      }
      lightOnAvg = diodeSensorValue / 30;
      Serial.print(lightOnAvg - lightOffAvg);
      Serial.print("\n");
      ODZero += lightOnAvg - lightOffAvg;
      digitalWrite(ledPin, LOW);
      delay(10);
    }
    ODZero /= 10;
    Serial.print("Done. ODZero = ");                       
    Serial.print(ODZero);
    Serial.print("\n");
  }
  
  diodeReading = 0;
  for (int i = 0; i < 5; i++) {
    diodeSensorValue = 0;
    for (int j = 0; j < 30; j++) {
      diodeSensorValue += analogRead(diodePin);
      delay(10);
    }
    lightOffAvg = diodeSensorValue / 30;
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(1);
    diodeSensorValue = 0;
    for (int j = 0; j < 30; j++) {
      diodeSensorValue += analogRead(diodePin);
      delay(10);
    }
    lightOnAvg = diodeSensorValue / 30;
    //Serial.print("Avg On = ");
    //Serial.print(lightOnAvg);
    //Serial.print("\n");
    //Serial.print("Avg Off = ");
    //Serial.print(lightOffAvg);
    //Serial.print("\n");
    diodeReading += lightOnAvg - lightOffAvg;
    //Serial.print(lightOnAvg - lightOffAvg);
    //Serial.print("\n");
    digitalWrite(ledPin, LOW);
    delay(10);
  }
  diodeReading /= 5;
  Serial.print("Reading = ");
  Serial.print(32.399 * (-log10(float(diodeReading) / float(ODZero))),4);
  Serial.print("\n");
}

