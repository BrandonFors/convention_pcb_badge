#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>


// Button Pins
#define BUT_1_PIN 32
#define BUT_2_PIN 22
#define BUT_3_PIN 21

// E-Paper pins
#define MOSI_PIN 13 // SPI
#define SCLK_PIN 14 // SPI
#define CS_PIN   27 // GPIO OUT
#define DC_PIN   26 // GPIO OUT
#define RET_PIN  25 // GPIO OUT // Hardware Reset
#define BUSY_PIN 33 // GPIO IN

//LEDS
#define RED_LED_PIN 16
#define YEL_LED_PIN 17



#endif