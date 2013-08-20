#include "Arduino.h"
#include "Temperature.h"

TemperatureSensor::TemperatureSensor(int pin) : pin_(pin) {
    pinMode(pin_, INPUT);
}

float TemperatureSensor::getTemperature() {
    float voltage = (float(analogRead(pin_)) / 4095) * 3.26; //Map analog value to voltage
    temperature_ = ((voltage / (3.26 / 5)) - 1.375) / .0225; //Transfer function
    return temperature_;
}

Thermoresistor::Thermoresistor(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    setPulseWidth(0);
    state_ = 0;
}

void Thermoresistor::setPulseWidth(float temperature) {
    // Transfer function goes here
    pulse_width_ = (int) temperature;
    if (state_)
      analogWrite(pin_, pulse_width_);
}

void Thermoresistor::setState(bool on) {
  if(on) {
    state_ = 1;
    analogWrite(pin_, pulse_width_);
  }
  else {
    state_ = 0;
    analogWrite(pin_, 0);
  }
}

bool Thermoresistor::getState() {
  return state_;
}
