#ifndef ANALOGOUTPUTDEVICE_H
#define	ANALOGOUTPUTDEVICE_H

#include "Arduino.h"
#include "DigitalOutputDevice.h"

class AnalogOutputDevice : public DigitalOutputDevice {
public:
    AnalogOutputDevice(int pin);
    void setState(bool on);
    void setPulseWidth(int pulse_width);
protected:
    int pulse_width_;
};

#endif	/* ANALOGOUTPUTDEVICE_H */
