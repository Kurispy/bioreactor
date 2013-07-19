#include <Temperature.h>
#include <OpticalDensity.h>

TemperatureSensor temp_sen(A1);
Thermoresistor thermres(9);

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  if(Serial.available() > 0) {
    thermres.setPulseWidth(Serial.parseInt());
  }
  delay(1000);
  Serial.println(temp_sen.getTemperature());
}



