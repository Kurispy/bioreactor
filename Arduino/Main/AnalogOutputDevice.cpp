#include "Arduino.h"
#include "AnalogOutputDevice.h"

AnalogOutputDevice::AnalogOutputDevice(int pin) 
  : DigitalOutputDevice(pin) 
{
  pulse_width_ = 0;
}

void AnalogOutputDevice::setState(bool on) {
  if(on) {
    state_ = 1;
    analogWrite(pin_, pulse_width_);
  }
  else {
    state_ = 0;
    analogWrite(pin_, 0);
  }
}

void AnalogOutputDevice::setPulseWidth(int pulse_width) {
  pulse_width_ = pulse_width;
  if (state_)
    analogWrite(pin_, pulse_width_);
}
