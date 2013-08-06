#include "Temperature.h"
#include "OpticalDensity.h"
#include "Communication.h"

TemperatureSensor *temp_sen = new TemperatureSensor(A1);
Thermoresistor *thermres = new Thermoresistor(9);
ODSensor *od_sen = new ODSensor(A2, 10);
float desired_temperature = 25.0;
char buffer[8];

void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
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
  
  switch(packet_type) {
    case BCommunication::Config: {
      // This could be dangerous. Should be changed to timeout
      while(!Serial.available());
      BCommunication::ConfigType config_type = 
        (BCommunication::ConfigType) Serial.read();
        
      switch(config_type) {
        case BCommunication::CalibrateOD:
          od_sen->calibrate();
          break;
        case BCommunication::SetTemperature: {
          while(!Serial.available());
          for(int i = 0; Serial.peek() != '\n'; i++) 
          {
            buffer[i] = Serial.read();
            while(!Serial.available());
          }
          Serial.read();
          desired_temperature = *(reinterpret_cast<float *>(buffer));
          thermres->setPulseWidth(desired_temperature);
          break;
        }
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
      Serial.print(temp_sen->getTemperature());
      Serial.write('\n');
      Serial.flush();
      break;
    case BCommunication::Air:
      
      break;
    case BCommunication::pH:
      Serial.write(BCommunication::pH);
      Serial1.print("r\r");
      while(!Serial1.available());
      for(int i = 0; Serial1.peek() != '\r'; i++) 
      {
        buffer[i] = Serial1.read();
        while(!Serial1.available());
      }
      Serial1.read();
      Serial.print(buffer);
      Serial.write('\n');
      Serial.flush();
      break;
    default:
    
      break;
  }
}

void serialEvent1() {
  
}


// This is needed due to a bug in 1.5.2 (Do not modify this)
void serialEventRun(void) {
  if (Serial.available())
    serialEvent();
  if (Serial1.available())
    serialEvent1();
}
