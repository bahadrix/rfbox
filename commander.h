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
private:
    void sendPong(uint8_t target);

protected:
    Broker *broker;

public:
    static const uint8_t POS_DOMAIN_INDEX = 0x0;
    static const uint8_t POS_COMMAND_SET = 0x1;
    static const uint8_t POS_COMMAND_INDEX = 0x2;
    static const uint8_t POS_PARAMS = 0x3;

    static const uint8_t CI_PING = 0x1;
    static const uint8_t CI_PONG = 0x2;
    static const uint8_t CI_CTR = 0x3;
    static const uint8_t CI_SET = 0x4;
    static const uint8_t CI_GET = 0x5;
    static const uint8_t CI_STATE = 0x6;

    static const uint8_t EVERYONE = 0x0;

    uint8_t domainIndex;
    uint8_t setIndex;

    Commander(Broker *broker, uint8_t domainIndex, uint8_t setIndex) : broker(broker), domainIndex(domainIndex),
                                                                       setIndex(setIndex) {}
    void callToRoll();
    void sendPing(uint8_t receiver);
    void sendState(uint8_t receiver, uint8_t target, const uint8_t *values, uint8_t valuesSize);
    void sendState(uint8_t receiver, uint8_t target, const uint8_t *values);

    void send(uint8_t receiver, uint8_t commandIndex, const uint8_t *params, uint8_t size);
    void send(uint8_t receiver, uint8_t commandIndex);

    static void parseCommand(const uint8_t *payload, uint8_t size, Command *command);

    virtual void onCommand(uint8_t senderId, const Command *command);


    virtual void onPong(uint8_t senderId, const uint8_t params[24]);
    virtual void onSet(uint8_t senderId, const uint8_t params[24]);
    virtual void onGet(uint8_t senderId, const uint8_t params[24]);
    virtual void onState(uint8_t senderId, const uint8_t params[24]);

};


#endif //RFBOX_COMMANDER_H
