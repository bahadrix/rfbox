//
// Created by Bahadir Katipoglu on 5.07.2020.
//

#ifndef RFBOX_BASICCOMMANDER_H
#define RFBOX_BASICCOMMANDER_H


#include "commander.h"

class BasicCommander : public Commander {
public:
    static const uint8_t CI_SET = 0x1;
    static const uint8_t CI_GET = 0x2;
    static const uint8_t CI_STATE = 0x3;

    inline explicit BasicCommander(Broker *broker) : Commander(broker, 0x0,0x1) {};

    void sendState(uint8_t receiver, uint8_t targetObject, uint8_t *value);

    void onCommand(uint8_t senderId, const Command *command) override;


    void onSet(uint8_t senderId, const uint8_t params[24]);
    void onGet(uint8_t senderId, const uint8_t params[24]);
    void onState(uint8_t senderId, const uint8_t params[24]);
};


#endif //RFBOX_BASICCOMMANDER_H
