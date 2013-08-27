#include "Temperature.h"
#include "OpticalDensity.h"
#include "Communication.h"
#include "Solenoid.h"
#include "Motor.h"

TemperatureSensor *temp_sen = new TemperatureSensor(A2);
Thermoresistor *thermres = new Thermoresistor(9);
ODSensor *od_sen = new ODSensor(A0, 13);
Solenoid *solenoid = new Solenoid(11);
Motor *motor = new Motor(7);
float desired_temperature = 25.0;
char buffer[8];
int k = 0, i = 0;
float ph = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  analogReadResolution(12);
}

// This is where any sort of any sort of internal feedback
// actions should be placed
void loop() {
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
      waitForSerialData(500);
      BCommunication::ConfigType config_type = 
        (BCommunication::ConfigType) Serial.read();
        
      switch(config_type) {
        case BCommunication::CalibrateOD:
          od_sen->calibrate();
          break;
        case BCommunication::SetTemperature: {
          waitForSerialData(500);
          for(i = 0; Serial.peek() != '\n' && i < 8; i++) 
          {
            buffer[i] = Serial.read();
            waitForSerialData(500);
          }
          Serial.read();
          desired_temperature = *(reinterpret_cast<float *>(buffer));
          thermres->setPulseWidth(desired_temperature);
          break;
        }
        case BCommunication::SetSolenoidState: {
          waitForSerialData(500);
          solenoid->setState(Serial.read());
          Serial.read();
          break;
        }
        case BCommunication::SetMotorState: {
          waitForSerialData(500);
          motor->setState(Serial.read());
          Serial.read();
          break;
        }
        case BCommunication::SetMotorSpeed: {
          waitForSerialData(500);
          for(i = 0; Serial.peek() != '\n' && i < 8; i++) 
          {
            buffer[i] = Serial.read();
            waitForSerialData(500);
          }
          Serial.read();
          motor->setPulseWidth(*(reinterpret_cast<int *>(buffer)));
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
      Serial.print(++k);
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
      Serial1.print("r\r");
      waitForSerial1Data(500);
      for(i = 0; Serial1.peek() != '\r' && i < 8; i++) 
      {
        buffer[i] = Serial1.read();
        waitForSerial1Data(500);
      }
      buffer[i] = '\0';
      Serial1.read();
      Serial.write(BCommunication::pH);
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

// Waits ms milliseconds for serial data to arrive. Returns 1 if it
// times out, 0 otherwise.
int waitForSerialData(unsigned long ms) {
  unsigned long start = millis();
  while(!Serial.available()) {
    if (millis() - start > ms)
      return 1;
  }
  return 0;
}

int waitForSerial1Data(unsigned long ms) {
  unsigned long start = millis();
  while(!Serial1.available()) {
    if (millis() - start > ms)
      return 1;
  }
  return 0;
}
  
