/*
 * File:   led.c
 * Author: ladrift
 *
 * Created on July 1, 2017, 4:27 PM
 */


#include <xc.h>
#include <stdint.h>

#include "led.h"

uint8_t numbers[11] = {
  0b01111110,  // 0
  0b00011000,  // 1
  0b01101101,  // 2
  0b00111101,  // 3
  0b00011011,  // 4
  0b00110111,  // 5
  0b01110111,  // 6
  0b00011100,  // 7
  0b01111111,  // 8
  0b00111111,  // 9
  0b00000000,  // none
};

/**
 * Initialize for two LEDs.
 */
void LED_Init() {
    // Port A
    ANSELA = 0x0;
    TRISA = 0x0;
    // Port C
    TRISC = 0x0;
}

/**
 * Set the value on LED specified by which.
 * When which == 0, set value on LED at port A.
 * When which == 1, set value on LED at port C.
 */
void LED_Set(uint8_t which, uint8_t value) {
    if (which == 0) {
        // Operate on LED at Port A.
        LATA = ~numbers[value];
    } else if (which == 1) {
        // Operate on LED at Port A.
        LATC = ~numbers[value];
    }
}

/**
 * Clear the value on LED specified by which.
 * When which == 0, set value on LED at port A.
 * When which == 1, set value on LED at port C.
 */
void LED_Clear(uint8_t which) {
    if (which == 0) {
        // Operate on LED at Port A.
        LATA = ~0x0;
    } else if (which == 1) {
        // Operate on LED at Port A.
        LATC = ~0x0;
    }
}
