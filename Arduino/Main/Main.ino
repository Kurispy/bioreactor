#include "Temperature.h"
#include "OpticalDensity.h"
#include "Communication.h"

TemperatureSensor temp_sen(A1);
Thermoresistor thermres(9);

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  
}

// Run whenever serial data is available to be read
void serialEvent() {
  // This will need to be changed to Serial.parseInt() if there are
  // ever more than 9 packet types. This method is faster though
  PacketType packet_type = (PacketType) (Serial.read() - '0');
  
  switch(packet_type) {
    case config:
      
      break;
    case od:
      
      break;
    case dox:
      
      break;
    case temp:
      
      break;
    case air:
      
      break;
    case ph:
      
      break;
    default:
    
      break;
  }
}

// This is needed due to a bug in 1.5.2 (Do not modify this)
void serialEventRun(void) {
  if (Serial.available())
    serialEvent();
}
