#ifndef DIGITALOUTPUTDEVICE_H
#define	DIGITALUTPUTDEVICE_H

#include "Arduino.h"

class DigitalOutputDevice {
public:
    DigitalOutputDevice(int pin);
    virtual void setState(bool on);
    bool getState();
    void setPulseInterval(unsigned long pulse_interval);
    void setPulseDuration(unsigned long pulse_duration);
    unsigned long getPulseInterval();
    unsigned long getPulseDuration();
    void setLastPulse(unsigned long last_pulse);
    unsigned long getTimeSinceLastPulse();
protected:
    int pin_;
    bool state_;
    bool is_pulsed_;
    unsigned long pulse_interval_;
    unsigned long pulse_duration_;
    unsigned long last_pulse_;
};

#endif	/* DIGITALOUTPUTDEVICE_H */
