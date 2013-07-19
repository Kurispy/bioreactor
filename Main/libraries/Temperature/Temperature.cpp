#include "Arduino.h"
#include "Temperature.h"

TemperatureSensor::TemperatureSensor(int pin) : pin_(pin) {
    pinMode(pin_, INPUT);
}

float TemperatureSensor::getTemperature() {
    float voltage = 2 * (float(analogRead(pin_)) / 4095) * 3.3; //Map analog value to voltage
    temperature_ = ((voltage / (5.04 / 5)) - 1.375) / .0225; //Transfer function
    return temperature_;
}

Thermoresistor::Thermoresistor(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT);
    setPulseWidth(0);
}

void Thermoresistor::setPulseWidth(int pulse_width) {
    pulse_width_ = pulse_width;
    analogWrite(pin_, pulse_width_);
}
