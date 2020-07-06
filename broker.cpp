//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#include "broker.h"
#include "util.h"
#include "commander.h"

Broker::Broker(uint64_t poolId, uint8_t deviceId, RF24 *radio)
        : poolId(poolId), deviceId(deviceId) {
    this->radio = radio;
}

bool Broker::send(uint8_t receiver, const char *payload, uint8_t payloadSize) {
    radio->stopListening();
    this->radio->openWritingPipe(this->poolId);

    uint8_t pos = 0;
    this->buffer[pos++] = receiver;
    this->buffer[pos++] = this->deviceId;
    this->buffer[pos++] = payloadSize;

    for (uint8_t i = 0; i < payloadSize && pos < MAX_PACKAGE_SIZE; i++) {
        this->buffer[pos++] = *(payload + i);
    }
    //printf("Sending message size of %d to broker of %x\n", pos, this->poolId);
    return this->radio->write(this->buffer, pos);
}

void Broker::listen() {

    static const uint8_t payloadPrefixCount = 3;

    this->radio->startListening();
    this->radio->openReadingPipe(1, this->poolId);

    if (!radio->available()) { // Wait for message
        return;
    }


    static uint8_t buffer[MAX_PACKAGE_SIZE] = {0};
    radio->read(&buffer, MAX_PACKAGE_SIZE);

    /*
    Serial.print("Messageo: ");
    Util::print_u8(buffer, MAX_PACKAGE_SIZE);
    Serial.println("");
    */

    if (buffer[0] != this->deviceId && buffer[0] != Commander::EVERYONE) {
        // this message is not for us
        return;
    }

    // ** Message format: { receiver, sender, payloadSize, payload { domainIndex, setIndex, commandIndex, params } }

    // Message sent to us, lets process it
    static uint8_t pos, payloadSize, senderId;
    pos = 1; // Reset position
    senderId = buffer[pos++];
    payloadSize = buffer[pos++];

    static Command command = {
            .domainIndex=0,
            .setIndex=0,
            .index=0,
            .params={0},
    };

    Commander::parseCommand(buffer + pos, payloadSize, &command);


    //printf("CMD Info: D: %d S: %d I: %d\n", command.domainIndex, command.setIndex, command.index);

    commander->onCommand(senderId, &command);

}

void Broker::setCommander(Commander *commander) {
    this->commander = commander;
}





