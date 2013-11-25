#ifndef SOLENOID_H
#define	SOLENOID_H

#include "Arduino.h"
#include "AnalogOutputDevice.h"

class Solenoid : public AnalogOutputDevice {
public:
    Solenoid(int pin);
};

#endif	/* SOLENOID_H */
