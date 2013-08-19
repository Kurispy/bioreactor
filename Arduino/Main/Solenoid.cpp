#include "Arduino.h"
#include "Solenoid.h"

Solenoid::Solenoid(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    state_ = 0;
    digitalWrite(pin_, LOW);
}

void Solenoid::setState(bool on) {
  if(on) {
    state_ = 1;
    digitalWrite(pin_, HIGH);
  }
  else {
    state_ = 0;
    digitalWrite(pin_, LOW);
  }
}

bool Solenoid::getState() {
  return state_;
}
