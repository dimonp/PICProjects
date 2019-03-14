/*
 * File:   blink.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTRCIO & 
    _WDTE_OFF & 
    _PWRTE_ON & 
    _MCLRE_ON & 
    _BOREN_OFF & 
    _CP_OFF & 
    _CPD_OFF;

int main() {
    // calibrate internal oscillator 4Mhz
    __asm__("             \n \
        call 0x03ff       \n \
        bsf STATUS,RP0    \n \
        movwf OSCCAL      \n \
        bcf STATUS, RP0   \n \
    ");

    INTCON  = 0;                // Disable interrupts
    TRISIO = 0;                 // All pins are output
    GPIO = 0;                   // Make all pins 0
    NOT_GPPU = 1;               // Disable pull-ups
    CMCON = 0b111;              // Disable comparator

    TMR0 = 0;                   // Clear Timer0 register
    T0IF = 0;                   // Clear overflow flag
    T0SE = 0;                   // Timer0 increment on rising edge
    T0CS = 0;                   // Timer0 increment from internal clock
    PSA = 0;                    // Prescaler is assigned to the Timer0 module 
    OPTION_REGbits.PS = 0b111;  // Prescaller is 1:256

    uint8_t counter = 0;
    while(1) {
        if (T0IF) { // overflow
            T0IF = 0; // Clear overflow flag
            counter++;

            // Led blinking with (Fosc/4=1Mhz)/(256*256*2^4) ~ 0.95 Hz frequency
            GPIO0 = (counter & 0b10000) >> 4;  
        }
    }
}