//
// Created by Bahadir Katipoglu on 1.07.2020.
//

#ifndef RFBOX_BROKER_H
#define RFBOX_BROKER_H

#define MAX_PACKAGE_SIZE 32


#include <stdint.h>
#include <RF24.h>


class Commander;

class Broker {

private:
    uint64_t poolId;
    uint8_t deviceId;
    RF24 *radio{};
    uint8_t buffer[MAX_PACKAGE_SIZE] = {0};
    Commander *commander;
    bool copyToSerial;
public:
    Broker(uint64_t poolId, uint8_t deviceId, RF24 *radio, bool copyToSerial);

    void setCommander(Commander *commander);

    bool send(uint8_t receiver, const char *payload, uint8_t payloadSize);

    void listen();


};


#endif //RFBOX_BROKER_H
