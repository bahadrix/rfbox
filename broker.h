//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#ifndef RFBOX_POOL_H
#define RFBOX_POOL_H

#define MAX_PACKAGE_SIZE 32


#include <stdint.h>
#include <RF24.h>


class Broker {
private:
    uint64_t poolId;
    uint8_t deviceId;
    RF24 *radio{};
    uint8_t buffer[MAX_PACKAGE_SIZE] = {0};

public:
    Broker(uint64_t poolId, uint8_t deviceId, RF24 *radio);
    static RF24* defaultRadio(uint16_t cePin, uint16_t csnPin) {
        auto radio = new RF24(cePin, csnPin);
        radio->begin();
        radio->setAutoAck(true);
        radio->setPALevel(RF24_PA_MAX);   // set power level
        radio->setChannel(0x76);
        radio->setDataRate(RF24_1MBPS);
        radio->enableDynamicPayloads();
        radio->powerUp();
        return radio;
    }
    bool send(uint8_t target, const char *payload, uint8_t payloadSize);
    uint8_t listen(uint8_t *message, uint8_t *senderId);

};


#endif //RFBOX_POOL_H
