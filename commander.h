//
// Created by Bahadir Katipoglu on 4.07.2020.
//

#ifndef RFBOX_COMMANDER_H
#define RFBOX_COMMANDER_H

#include <Arduino.h>
#include "broker.h"

const uint8_t MAX_PARAMS_SIZE = 24; // 0x18 for hex lovers
struct Command {
    uint8_t domainIndex{};
    uint8_t setIndex{};
    uint8_t index{};
    uint8_t params[MAX_PARAMS_SIZE] = {0};
};


/**
 * Commander abstract class
 */
class Commander {
protected:
    Broker *broker;

public:
    static const uint8_t POS_DOMAIN_INDEX = 0x0;
    static const uint8_t POS_COMMAND_SET = 0x1;
    static const uint8_t POS_COMMAND_INDEX = 0x2;
    static const uint8_t POS_PARAMS = 0x3;

    static const uint8_t EVERYONE = 0x0;

    uint8_t domainIndex;
    uint8_t setIndex;

    Commander(Broker *broker, uint8_t domainIndex, uint8_t setIndex) : broker(broker), domainIndex(domainIndex),
                                                                       setIndex(setIndex) {}

    void send(uint8_t target, uint8_t commandIndex, const uint8_t *params, uint8_t size);
    void send(uint8_t target, uint8_t commandIndex);
    static void parseCommand(const uint8_t *payload, uint8_t size, Command *command);

    virtual void onCommand(uint8_t senderId, const Command *command) = 0;
};


#endif //RFBOX_COMMANDER_H
