#include <Arduino.h>
#include <EEPROM.h>
#include <RF24.h>
#include "broker.h"
#include "serialcontroller.h"
#include <printf.h>

#define EEPROM_DEVICE_ID_SLOT 11
const uint64_t POOL_ID = 0x4241484158LL;
const int PIN_CE = 8;
const int PIN_CSN = 9;
const int PIN_MASTER = 2;

Broker *broker;
SerialController *serialController;
Commander *commander;
char *serialMessage;

uint8_t deviceID; // will be read from eeprom

bool isMaster();


void setup() {
    //EEPROM.write(EEPROM_DEVICE_ID_SLOT, 10);
    deviceID = EEPROM.read(EEPROM_DEVICE_ID_SLOT);

    printf_begin();

    Serial.begin(57600);
    Serial.println("Setting up");
    // Master Jumper settings
    pinMode(PIN_MASTER, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    volatile bool masta = isMaster();



    auto radio = new RF24(PIN_CE, PIN_CSN);
    radio->begin();
    radio->setAutoAck(false);
    radio->setPALevel(RF24_PA_MAX);   // set power level
    radio->setChannel(0x76);
    radio->setDataRate(RF24_1MBPS);
    radio->enableDynamicPayloads();
    radio->powerUp();

    broker = new Broker(POOL_ID, deviceID, radio, false);



    broker->setCommander(commander);


    serialController = new SerialController(&Serial);

    printf("Device %d initialized as %s\n", deviceID, masta ? "master" : "slave");

}

bool isMaster() {
    return digitalRead(PIN_MASTER) == LOW;
}

void processSerialCommand() {

    if (strncasecmp("HELLO", serialMessage, 5) == 0) {
        Serial.println("Hello to you dude!");;
    } else if (strncasecmp("S", serialMessage, 1) == 0) {
        Serial.println("Sending message");
        broker->send(20, "domates", 7);
    }

}



void testLoop() {

    if (isMaster()) {
        if (millis() % 2000 == 0) {
            //Serial.println("Ping to 30");
            //systemCommander->sendPing(30);



        }
    }

}

void loop() {

    // Run broker loop
    broker->listen();

    // Check incoming serial messages
    if (serialController->listen(&serialMessage) > 0) {
        processSerialCommand();
    }

    testLoop();

}

