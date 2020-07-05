//
// Created by Bahadir Katipoglu on 5.07.2020.
//

#ifndef RFBOX_UTIL_H
#define RFBOX_UTIL_H


#include <stdint.h>
#include <HardwareSerial.h>

class Util {
public:
    static void print_u8(const uint8_t *buffer, uint8_t size) {
        for (uint8_t i = 0; i < size; i++) {
            printf("%03d ", buffer[i]);
        }
    }
};



#endif //RFBOX_UTIL_H
