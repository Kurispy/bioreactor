#ifndef OPTICALDENSITY_H
#define	OPTICALDENSITY_H

#include "Arduino.h"

class ODSensor {
public:
    ODSensor(int photodiode_pin, int led_pin);
    float getOD();
    void calibrate();
private:
    int is_calibrated_;
    int photodiode_pin_;
    int led_pin_;
    int zero_reading_;
    int reading_;
};

#endif	/* OPTICALDENSITY_H */

