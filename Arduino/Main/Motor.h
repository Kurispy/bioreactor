#ifndef MOTOR_H
#define	MOTOR_H

#include "Arduino.h"

class Motor {
public:
    Motor(int pin);
    void setState(bool on);
    bool getState();
    void setPulseWidth(int pulse_width);
private:
    int pin_;
    bool state_;
    int pulse_width_;
};

#endif	/* MOTOR_H */
