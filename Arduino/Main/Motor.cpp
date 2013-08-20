#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    state_ = 0;
    pulse_width_ = 0;
    analogWrite(pin_, 0);
}

void Motor::setState(bool on) {
  if(on) {
    state_ = 1;
    analogWrite(pin_, pulse_width_);
  }
  else {
    state_ = 0;
    analogWrite(pin_, 0);
  }
}

bool Motor::getState() {
  return state_;
}

void Motor::setPulseWidth(int pulse_width) {
  pulse_width_ = pulse_width;
  if (state_)
    analogWrite(pin_, pulse_width_);
}
