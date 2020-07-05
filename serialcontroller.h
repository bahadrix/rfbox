//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#ifndef RFBOX_SERIALCONTROLLER_H
#define RFBOX_SERIALCONTROLLER_H



#include <stdint.h>
#include <HardwareSerial.h>

class SerialController {
    char *buffer;
    HardwareSerial *serial;
    uint8_t pos;
    bool clear;
public:
    explicit SerialController(HardwareSerial *serial);

    uint8_t listen(char **message);


};


#endif //RFBOX_SERIALCONTROLLER_H
