/*
 * File:   blink.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>
#include "debounce.h"

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTRCIO & 
    _WDTE_OFF & 
    _PWRTE_ON & 
    _MCLRE_ON & 
    _BOREN_OFF & 
    _CP_OFF & 
    _CPD_OFF;

int main() {
    // calibrate internal oscillator
    __asm__("             \n \
        call 0x03ff       \n \
        bsf STATUS,RP0    \n \
        movwf OSCCAL      \n \
        bcf STATUS, RP0   \n \
    ");

    INTCON  = 0;                // Disable interrupts

    // I/O pins configuration
    TRISIO = 0b010000;          // GP4 pin is input, rest are output
    GPIO = 0;                   // Make all pins 0
    NOT_GPPU = 1;               // Button on GP4 has own pull-up
    CMCON = 0b111;              // Disable comparator

    uint8_t ledVal = 0b001;
    GPIO = ledVal;
    while(1) {
        if (debounce(GPIO4)) {
            resetDebounce();

            ledVal = (ledVal+1) & 0b111;
            GPIO = ledVal;
        }
    }
}