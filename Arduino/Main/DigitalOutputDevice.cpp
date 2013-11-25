#include "Arduino.h"
#include "DigitalOutputDevice.h"

DigitalOutputDevice::DigitalOutputDevice(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    is_pulsed_ = 0;
    pulse_interval_ = 0;
    pulse_duration_ = 0;
    
    setState(0);
}

void DigitalOutputDevice::setState(bool on) {
  if(on) {
    state_ = 1;
    digitalWrite(pin_, HIGH);
  }
  else {
    state_ = 0;
    digitalWrite(pin_, LOW);
  }
}

bool DigitalOutputDevice::getState() {
  return state_;
}

void DigitalOutputDevice::setPulseInterval(unsigned long pulse_interval) {
  pulse_interval_ = pulse_interval;
}

void DigitalOutputDevice::setPulseDuration(unsigned long pulse_duration) {
  pulse_duration_ = pulse_duration;
}
