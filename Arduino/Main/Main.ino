#include "Temperature.h"
#include "OpticalDensity.h"
#include "Communication.h"

TemperatureSensor *temp_sen = new TemperatureSensor(A1);
Thermoresistor *thermres = new Thermoresistor(9);
ODSensor *od_sen = new ODSensor(A2, 10);


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
  BCommunication::PacketType packet_type = (BCommunication::PacketType) (Serial.read());
  
  // Data is sent as chars and not bytes due to the way Qt reads
  // from serial ports. This might be changed if it becomes an issue
  switch(packet_type) {
    case BCommunication::Config:
      
      break;
    case BCommunication::OD:
      Serial.write(BCommunication::OD);
      Serial.print(od_sen->getOD());
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::DO:
      Serial.write(BCommunication::DO);
      Serial.print(345.096);
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::Temperature:
      Serial.write(BCommunication::Temperature);
      Serial.print(temp_sen->getTemperature());
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::Air:
      
      break;
    case BCommunication::pH:
      Serial.write(BCommunication::pH);
      Serial.print(3452.3564);
      Serial.write('\n');
      Serial.flush();
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
