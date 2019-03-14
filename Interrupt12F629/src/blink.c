/*
 * File:   blink.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>
#include "delays.h"

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTRCIO & 
    _WDTE_OFF & 
    _PWRTE_ON & 
    _MCLRE_ON & 
    _BOREN_OFF & 
    _CP_OFF & 
    _CPD_OFF;

volatile uint8_t ledVal = 0b001;

// Interrupt on change switch, should be debounced.
void interrupt(void) __interrupt(0) {
    if (GPIO4 == 0) {
        // circular left shift
        ledVal = ((ledVal << 1) | ((ledVal >> 2) & 1)) & 0b111;
    }
    GPIF = 0;
}

int main() {
    // calibrate internal oscillator
    __asm__("             \n \
        call 0x03ff       \n \
        bsf STATUS,RP0    \n \
        movwf OSCCAL      \n \
        bcf STATUS, RP0   \n \
    ");

    TRISIO = 0b010000;          // GP4 pin is input, rest are output
    GPIO = 0;                   // Make all pins 0
    NOT_GPPU = 1;               // Button on GP4 has own pull-up
    CMCON = 0b111;              // Disable comparator

    INTCON  = 0;
    GIE = 1;                    // all interrupts are enabled
    GPIE = 1;                   // external interrupt enabled
    IOC4 = 1;                   // Interrupt-on-change GP4
    
    while(1) {
        GPIO = ledVal;
        delay_ms10(5);
        GPIO = 0;
        delay_ms10(5);
    }
}