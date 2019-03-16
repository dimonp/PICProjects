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

volatile uint8_t ledVal = 1;
volatile uint8_t counter = 0;

// Interrupt on change switch, should be debounced.
void interrupt(void) __interrupt(0) {
    T0IF = 0; // Clear overflow flag

    counter++;
    if (counter >= 242) { // ~ 1sec 
        counter = 0;

        if (GPIO0 | GPIO1 | GPIO2) {
            GPIO = 0;
        } else {
            GPIO = ledVal;
        }
    }
}

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
    NOT_GPPU = 1;               // Disable pull-ups
    CMCON = 0b111;              // Disable comparator

    // Timer0 configuration
    TMR0 = 0;                   // Clear Timer0 register
    T0IF = 0;                   // Clear overflow flag
    T0SE = 0;                   // Timer0 increment on rising edge
    T0CS = 0;                   // Timer0 increment from internal clock
    PSA = 0;                    // Prescaler is assigned to the Timer0 module 
    OPTION_REGbits.PS = 0b010;  // Prescaler is 1:8
    T0IE = 1;                   // Enable TMR0 overflow interrupt 
    GIE = 1;                    // Enable all unmasked interrupts

    while(1) {
        if (debounce(GPIO4)) {
            resetDebounce();
            ledVal = ((ledVal << 1) | ((ledVal >> 2) & 1)) & 0b111;
        }
    }
}