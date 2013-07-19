#include "Arduino.h"
#include "OpticalDensity.h"

ODSensor::ODSensor(int photodiode_pin, int led_pin) : photodiode_pin_(photodiode_pin), led_pin_(led_pin) {
    pinMode(photodiode_pin_, INPUT);
    pinMode(led_pin_, OUTPUT);
}

float ODSensor::getOD() {
    int lightOnAvg, lightOffAvg, reading, sum;
    for (int i = 0; i < 5; i++) {
        sum = 0;
        for (int j = 0; j < 30; j++) {
            sum += analogRead(photodiode_pin_);
            delay(10);
        }
        lightOffAvg = sum / 30;
        digitalWrite(led_pin_, HIGH); //Turn LED on
        delayMicroseconds(1);
        sum = 0;
        for (int j = 0; j < 30; j++) {
            sum += analogRead(photodiode_pin_);
            delay(10);
        }
        lightOnAvg = sum / 30;
        reading += lightOnAvg - lightOffAvg;
        digitalWrite(led_pin_, LOW); //Turn LED off
        delay(10);
  }
  reading /= 5;
  return 32.399 * (-log10(float(reading) / float(zero_reading_)));
}

void ODSensor::calibrate() {
    int lightOffAvg, lightOnAvg, sum;
    zero_reading_ = 0;
    digitalWrite(led_pin_, LOW); //Turn LED off
    for(int i = 0; i < 10; i++)
    {
        sum = 0;
        for (int j = 0; j < 30; j++) {
            sum += analogRead(photodiode_pin_);
            delay(10);
        }
        lightOffAvg = sum / 30;
        digitalWrite(led_pin_, HIGH); //Turn LED on
        delayMicroseconds(1);
        sum = 0;
        for (int j = 0; j < 30; j++) {
            sum += analogRead(photodiode_pin_);
            delay(10);
        }
        lightOnAvg = sum / 30;
        zero_reading_ += lightOnAvg - lightOffAvg;
        digitalWrite(led_pin_, LOW);
        delay(10);
    }
    zero_reading_ /= 10;
}