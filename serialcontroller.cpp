//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#include "serialcontroller.h"

SerialController::SerialController(HardwareSerial *serial) : serial(serial) {
    this->buffer = new char [UINT8_MAX];
    this->pos = 0;
    this->clear = false;
    this->state = SCState::WAIT;
}

uint8_t SerialController::listen(char **message) {

    if (!Serial.available()) {
        return 0;
    }

    uint8_t c = Serial.read();

    switch (this->state) {
        case SCState::WAIT:
            if (c == COMMAND_STARTER) {
                this->state = SCState::READ_LENGTH;
                this->pos = 0;
            }
            break;
        case SCState::READ_LENGTH:
            this->currentPayloadSize = c; // -1 for current byte

            this->state = SCState::READ_MESSAGE;
            break;
        case SCState::READ_MESSAGE:
            this->buffer[pos++] = c;
            if (pos == this->currentPayloadSize) {
                this->state = SCState::WAIT;
                *message = this->buffer;
                return this->currentPayloadSize;
            }
            break;
    }

    return 0;
}
