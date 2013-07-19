#include <cstdlib>
#include <iostream>
#include <SerialStream.h>

using namespace LibSerial;

int main(int argc, char** argv) {
    float temp;
    int pw;
    
    SerialStream due("/dev/ttyACM0", std::ios_base::in);
    due.SetBaudRate(SerialStreamBuf::BAUD_9600);
    due.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    due.SetNumOfStopBits(1);
    due.SetParity(SerialStreamBuf::PARITY_NONE);
    due.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
    
    while (due.IsOpen()) {
        due >> temp;
        due >> pw;
        due.ignore();
        std::cout << temp << " " << pw << "\n";
    }
    return 0;
}

