//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#include "serialcontroller.h"

SerialController::SerialController(HardwareSerial *serial) : serial(serial) {
    this->buffer = new char [UINT8_MAX];
    this->pos = 0;
    this->clear = false;
}

uint8_t SerialController::listen(char **message) {

    if (Serial.available()) {
        if (this->clear) {
            this->pos = 0;
            this->clear = false;
        }
        int ch = Serial.read();


        if (ch == 10 || this->pos == UINT8_MAX) {
            this->clear = true;
            *message = this->buffer;
            return this->pos;
        }

        this->buffer[this->pos++] = ch;
    }



    return 0;
}
