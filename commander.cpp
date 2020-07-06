//
// Created by Bahadir Katipoglu on 4.07.2020.
//
#include "commander.h"
#include "util.h"

/**
 * Send command to target
 * @param receiver Target ID
 * @param commandIndex Index of command
 * @param params Parameter array
 * @param size Length of parameters
 */
void Commander::send(uint8_t receiver, uint8_t commandIndex, const uint8_t *params, uint8_t size) {
    static char cmdWithPrefixes[MAX_PACKAGE_SIZE] = {};
    static uint8_t pos, i;
    pos = 0;
    cmdWithPrefixes[pos++] = this->domainIndex;
    cmdWithPrefixes[pos++] = this->setIndex;
    cmdWithPrefixes[pos++] = commandIndex;

    for (i = 0; i < size; i++) {
        cmdWithPrefixes[pos++] = params[i];
    }
    this->broker->send(receiver, cmdWithPrefixes, pos);
}

void Commander::send(uint8_t receiver, uint8_t commandIndex) {
    this->send(receiver, commandIndex, nullptr, 0);
}

void Commander::parseCommand(const uint8_t *payload, uint8_t size, Command *command) {

    if (size < POS_PARAMS) {
        // we need  domain, command set and command id at least
        // so the message is for me but it's empty
        //Serial.println("Empty message");
        return;
    }

    /*
    Serial.print("Message to parse: ");
    Util::print_u8(payload, size);
    Serial.println("");
    */

    static uint8_t i;

    command->domainIndex = payload[POS_DOMAIN_INDEX];
    command->setIndex = payload[POS_COMMAND_SET];
    command->index = payload[POS_COMMAND_INDEX];
    //command->params = {0};

    //printf("INYT CMD Info: D: %d S: %d I: %d\n", command->domainIndex, command->setIndex, command->index);

    for (i = 0; i < MAX_PARAMS_SIZE; i++) {
        command->params[i] = payload[POS_PARAMS + i];
    }

}

void Commander::onCommand(uint8_t senderId, const Command *command) {

    if (command->domainIndex != this->domainIndex || command->setIndex != this->setIndex) {
        // this command is not for our domain or command set
        return;
    }

    if (copyToSerial) {
        Serial.write('@');
        Serial.write(senderId);
        Serial.write(command->domainIndex);
        Serial.write(command->setIndex);
        Serial.write(command->index);
        for (unsigned char param : command->params) {
            Serial.write(param);
        }
        Serial.write("\n");
    }


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

void Commander::sendPing(uint8_t receiver) {
    this->send(receiver, CI_PING);
}

void Commander::sendPong(uint8_t receiver) {
    auto lifetime = millis();
    auto ltp = (uint8_t *) &lifetime;

    this->send(receiver, CI_PONG, ltp, 4);
}

void Commander::callToRoll() {
    this->send(Commander::EVERYONE, CI_CTR);
}

void Commander::onPong(uint8_t senderId, const uint8_t *params) {
    volatile auto lifetime = (unsigned long *) params;
    //printf("Pong from %d LT: %lu\n", senderId, *lifetime);
}

void Commander::sendState(uint8_t receiver, uint8_t target, const uint8_t *values, uint8_t valuesSize) {

    static uint8_t params[MAX_PARAMS_SIZE] = {0};
    static uint8_t pos;
    pos = 0;
    params[pos++] = target;

    for (uint8_t i = 0; i < valuesSize; i++) {
        params[pos++] = values[i];
    }

    this->send(receiver, CI_STATE, params, pos);
}

void Commander::sendState(uint8_t receiver, uint8_t target, const uint8_t *values) {
    this->sendState(receiver, target, values, 1);
}

uint8_t Commander::commandBytes(Command *command, uint8_t *commandBytes) {



    return 0;
}


