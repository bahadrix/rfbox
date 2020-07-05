//
// Created by Bahadir Katipoglu on 5.07.2020.
//

#include "basiccommander.h"
#include "broker.h"
#include <Arduino.h>



void BasicCommander::onCommand(uint8_t senderId, const Command *command) {
    switch (command->index) {
        case CI_SET:
            onSet(senderId, command->params);
            break;
        case CI_GET:
            onGet(senderId, command->params);
            break;
        case CI_STATE:
            onState(senderId, command->params);
            break;
    }
}

void BasicCommander::sendState(uint8_t receiver, uint8_t targetObject, uint8_t *value) {

}

void BasicCommander::onSet(uint8_t senderId, const uint8_t *params) {

}

void BasicCommander::onGet(uint8_t senderId, const uint8_t *params) {

}

void BasicCommander::onState(uint8_t senderId, const uint8_t *params) {

}