#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

namespace BCommunication {
    enum PacketType {
        Config = '0',
        OD,
        Temperature,
        DO,
        pH,
        Air
    };
}

#endif	/* COMMUNICATION_H */
