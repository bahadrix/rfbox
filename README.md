# Arduino RFT library

Test Sample

```c++
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "rfbox.h"
#include <printf.h>

#define IS_TRANSMITTER

const int PIN_CE = 8;
const int PIN_CSN = 9;


RF24 radio(PIN_CE, PIN_CSN);

//address through which two modules communicate.
//const byte address[6] = "bxc01";
//const uint64_t pipe = 0xE0E0F1F1E0LL;
//const uint64_t pipe = 0x314E6F6465LL; // 1Node
//const uint64_t pipe = 0x324E6F6465LL; // 2Node
const uint64_t pipe = 0x65646f4e32LL;

#ifdef IS_TRANSMITTER

bool lastSendSuccessful = true;

void setup() {


    radio.begin();

    //set the address
    radio.openWritingPipe(pipe);
    radio.setPALevel(RF24_PA_MAX);   // set power level
    radio.setChannel(0x76);
    radio.setDataRate(RF24_1MBPS);
    radio.enableDynamicPayloads() ;
    radio.powerUp();
    //Set module as transmitter
    radio.stopListening();
}

void loop() {
    //Send message to receiver

    //const char text[] = "AAAAAAAAA";
    //const char text[] = "BBBBBBBBB";

    char text[32];

    sprintf(text, "C: %lu LS: %d", millis(), lastSendSuccessful);


    lastSendSuccessful = radio.write(text, sizeof(text));

    delay(100);
}

#else // Receiver ---

void setup() {
    Serial.begin(57600);
    printf_begin();
    printf("\n\rRF24 Initializing/\n\r");

    radio.begin();
    radio.setAutoAck(false);
    radio.setPALevel(RF24_PA_MAX);   // set power level
    radio.setChannel(0x76);
    radio.setDataRate(RF24_1MBPS);
    Serial.println("Listening pipe");
    radio.openReadingPipe(1, pipe);


    radio.enableDynamicPayloads();
    radio.powerUp();
    radio.printDetails();



}

void loop() {

    //Set module as receiver
    radio.startListening();
    //Read the data if available in buffer
    if (radio.available()) {

        char text[32] = {0};
        radio.read(&text, sizeof(text));
        Serial.println(text);

    }
}

#endif
```