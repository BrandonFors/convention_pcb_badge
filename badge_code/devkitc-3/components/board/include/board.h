#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>


// Button Pins
#define BUT_1_PIN 21
#define BUT_2_PIN 20
#define BUT_3_PIN 10

// E-Paper pins 
#define MOSI_PIN 7 // SPI
#define SCLK_PIN 8 // SPI
#define CS_PIN   9 // GPIO OUT
#define DC_PIN   6 // GPIO OUT
#define RET_PIN  4 // GPIO OUT // Hardware Reset
#define BUSY_PIN 5 // GPIO IN

//LEDS
#define RED_LED_PIN 0
#define YEL_LED_PIN 1



#endif