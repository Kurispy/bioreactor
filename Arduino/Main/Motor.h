#ifndef MOTOR_H
#define	MOTOR_H

#include "Arduino.h"
#include "AnalogOutputDevice.h"

class Motor : public AnalogOutputDevice {
public:
    Motor(int pin);
};

#endif	/* MOTOR_H */
