#include "Temperature.h"
#include "OpticalDensity.h"
#include "Communication.h"

TemperatureSensor *temp_sen = new TemperatureSensor(A1);
Thermoresistor *thermres = new Thermoresistor(9);
ODSensor *od_sen = new ODSensor(A2, 10);
float desired_temperature = 25.0; // Placeholder
char buffer[8];

void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  // This is where any sort of any sort of internal feedback
  // actions should be placed
  if(temp_sen->getTemperature() < desired_temperature)
    thermres->setState(1);
  else
    thermres->setState(0);
  
}

// Run whenever serial data is available to be read
void serialEvent() {
  BCommunication::PacketType packet_type = 
    (BCommunication::PacketType) Serial.read();
  
  // Data is sent as chars and not bytes due to the way Qt reads
  // from serial ports. This might be changed if it becomes an issue
  switch(packet_type) {
    case BCommunication::Config: {
      // This could be dangerous. Should be changed to timeout
      while(!Serial.available() == 0);
      BCommunication::ConfigType config_type = 
        (BCommunication::ConfigType) Serial.read();
        
      switch(config_type) {
        case BCommunication::CalibrateOD:
          od_sen->calibrate();
          break;
        case BCommunication::SetTemperature:
          while(!Serial.available());
          for(int i = 0; Serial.peek() != '\n'; i++) {
            buffer[i] = Serial.read();
          }
          Serial.read();
          desired_temperature = *(reinterpret_cast<float *>(buffer));
          thermres->setPulseWidth(desired_temperature);
          break;
      }
      break;
    }
    case BCommunication::OD:
      Serial.write(BCommunication::OD);
      Serial.print(od_sen->getOD());
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::DO:
      Serial.write(BCommunication::DO);
      Serial.print(12345);
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::Temperature:
      Serial.write(BCommunication::Temperature);
      Serial.print(desired_temperature);
      //Serial.print(temp_sen->getTemperature());
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::Air:
      
      break;
    case BCommunication::pH:
      Serial.write(BCommunication::pH);
      Serial.print(12345);
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
