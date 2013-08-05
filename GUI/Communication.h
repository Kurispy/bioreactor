#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

namespace BCommunication {
    enum PacketType {
        Config,
        OD,
        Temperature,
        DO,
        pH,
        Air,
        TestRequest
    };

    enum ConfigType {
        CalibrateOD,
        SetTemperature
    };
}

#endif	/* COMMUNICATION_H */
