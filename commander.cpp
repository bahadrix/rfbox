//
// Created by Bahadir Katipoglu on 4.07.2020.
//
#include "commander.h"
#include "util.h"

/**
 * Send command to target
 * @param target Target ID
 * @param commandIndex Index of command
 * @param params Parameter array
 * @param size Length of parameters
 */
void Commander::send(uint8_t target, uint8_t commandIndex, const uint8_t *params, uint8_t size) {
    static char cmdWithPrefixes[MAX_PACKAGE_SIZE] = {};
    static uint8_t pos, i;
    pos = 0;
    cmdWithPrefixes[pos++] = this->domainIndex;
    cmdWithPrefixes[pos++] = this->setIndex;
    cmdWithPrefixes[pos++] = commandIndex;

    for (i = 0; i < size; i++) {
        cmdWithPrefixes[pos++] = params[i];
    }
    this->broker->send(target, cmdWithPrefixes, pos);
}

void Commander::send(uint8_t target, uint8_t commandIndex) {

    this->send(target, commandIndex, nullptr, 0);
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