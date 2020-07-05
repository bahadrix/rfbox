//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#ifndef RFBOX_SERIALCONTROLLER_H
#define RFBOX_SERIALCONTROLLER_H



#include <stdint.h>
#include <HardwareSerial.h>

enum SCState {WAIT, READ_LENGTH, READ_MESSAGE};

class SerialController {
    const int COMMAND_STARTER = 64; // @ symbol
    char *buffer;
    uint8_t currentPayloadSize = 0;
    HardwareSerial *serial;
    uint8_t pos;
    bool clear;
    SCState state;
public:

    explicit SerialController(HardwareSerial *serial);

    uint8_t listen(char **message);


};


#endif //RFBOX_SERIALCONTROLLER_H
