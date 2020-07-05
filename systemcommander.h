//
// Created by Bahadir Katipoglu on 4.07.2020.
//

#ifndef RFBOX_SYSTEMCOMMANDER_H
#define RFBOX_SYSTEMCOMMANDER_H


#include "commander.h"

/**
 * Implementation of system commander
 */
class SystemCommander : public Commander {
private:
    void sendPong(uint8_t target);
public:
    static const uint8_t CI_PING = 0x1;
    static const uint8_t CI_PONG = 0x2;
    static const uint8_t CI_CTR = 0x3;

    inline explicit SystemCommander(Broker *broker) : Commander(broker, 0x0,0x0) {}


    void callToRoll();

    void sendPing(uint8_t target);

    void onCommand(uint8_t senderId, const Command *command) override;

    void onPong(uint8_t senderId, const uint8_t params[24]);
};



#endif //RFBOX_SYSTEMCOMMANDER_H
