#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>


// Button Pins
static const uint8_t BUT_1_PIN = 23;
static const uint8_t BUT_2_PIN = 22;
static const uint8_t BUT_3_PIN = 1;

// E-Paper pins
static const uint8_t MOSI = 13; // SPI
static const uint8_t SCLK = 14; // SPI
static const uint8_t CS = 27; // GPIO OUT
static const uint8_t DC = 26; // GPIO OUT
static const uint8_t RET = 25; // GPIO IN
static const uint8_t BUSY = 33; // GPIO IN



#endif