//
// Created by Bahadir Katipoglu on 4.07.2020.
//

#include "systemcommander.h"
#include "broker.h"


void SystemCommander::onCommand(uint8_t senderId, const Command *command) {

    switch (command->index) {
        case CI_PING: // Ping received
            sendPong(senderId);
            break;
        case CI_PONG:
            onPong(senderId, command->params);
            break;
        case CI_CTR:
            sendPong(senderId);
            break;
    }

}

void SystemCommander::sendPing(uint8_t target) {
    this->send(target, CI_PING);
}

void SystemCommander::sendPong(uint8_t target) {

    auto lifetime = millis();
    auto ltp = (uint8_t *) &lifetime;

    this->send(target, CI_PONG, ltp, 4);
}

void SystemCommander::onPong(uint8_t senderId, const uint8_t params[24]) {
    volatile auto lifetime = (unsigned long *) params;
    printf("Pong from %d LT: %lu\n", senderId, *lifetime);
}

void SystemCommander::callToRoll() {
    this->send(Commander::EVERYONE, CI_CTR);
}
