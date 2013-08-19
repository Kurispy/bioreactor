#ifndef SOLENOID_H
#define	SOLENOID_H

#include "Arduino.h"

class Solenoid {
public:
    Solenoid(int pin);
    void setState(bool on);
    bool getState();
private:
    int pin_;
    bool state_;
};

#endif	/* SOLENOID_H */
