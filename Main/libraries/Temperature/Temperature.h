#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#include "Arduino.h"

class TemperatureSensor {
public:
    TemperatureSensor(int pin);
    float getTemperature();
private:
    int pin_;
    float temperature_;
};

class Thermoresistor {
public:
    Thermoresistor(int pin);
    void setPulseWidth(int pulse_width);
private:
    int pin_;
    int pulse_width_;
};


#endif	/* TEMPERATURE_H */

