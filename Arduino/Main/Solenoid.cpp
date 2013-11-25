#include "Arduino.h"
#include "Solenoid.h"

Solenoid::Solenoid(int pin)
  : AnalogOutputDevice(pin)
{
  
}
