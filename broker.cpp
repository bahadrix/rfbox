//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#include "pool.h"

Broker::Broker(uint64_t poolId, uint8_t deviceId, RF24 *radio) : poolId(poolId), deviceId(deviceId) {
    this->radio = radio;
}

bool Broker::send(uint8_t target, const char *payload, uint8_t payloadSize) {
    radio->stopListening();
    this->radio->openWritingPipe(this->poolId);

    uint8_t pos = 0;
    this->buffer[pos++] = target;
    this->buffer[pos++] = this->deviceId;
    this->buffer[pos++] = payloadSize;

    for (uint8_t i = 0; i < payloadSize && pos < MAX_PACKAGE_SIZE; i++) {
        this->buffer[pos++] = *(payload + i);
    }
    printf("Sending message size of %d to pool of %x", pos, this->poolId);
    return this->radio->write(this->buffer, pos);
}

uint8_t Broker::listen(uint8_t *message, uint8_t *senderId) {

    this->radio->startListening();
    this->radio->openReadingPipe(1, this->poolId);

    if (!radio->available()) {
        return 0;
    }

    //radio->read(&this->buffer, sizeof(this->buffer));
    static uint8_t buffer[MAX_PACKAGE_SIZE] = {0};
    radio->read(&buffer, MAX_PACKAGE_SIZE);

    //printf("%d, %d\n", buffer[0], buffer[1]);

    //printf("DID %d\n", this->deviceId);

    //uint8_t deviceId = buffer[0];
    //uint8_t thisDeviceId = this->deviceId;
    //if (this->buffer[0] != this->deviceId) {
    //printf("Message device: %d, this device: %d\n", deviceId, thisDeviceId);
    if (buffer[0] != this->deviceId) {
        // this message is not for me
        Serial.println("Not for me");
        return 0;
    }


    uint8_t pos = 1;

    *senderId = buffer[pos++];

    uint8_t payloadSize = buffer[pos++];

    if (payloadSize == 0) {
        // the message is for me but it's empty
        return 0;
    }

    uint8_t i;

    for (i = 0; i < payloadSize; i++) {
        message[i] = buffer[pos++];
    }

    return i;
}


