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
    // calibrate internal oscillator Fosc=4Mhz
    __asm__("             \n \
        call 0x03ff       \n \
        bsf STATUS,RP0    \n \
        movwf OSCCAL      \n \
        bcf STATUS, RP0   \n \
    ");

    // Interrupt configuration
    INTCON  = 0;                // Disable interrupts
    PIE1 = 0;                   // Disable peripheral interrupts
    PIR1 = 0;                   // Clear peripheral interrupts Flags

    // I/O pins configuration
    TRISIO = 0;                 // All pins are output
    GPIO = 0;                   // Make all pins 0
    NOT_GPPU = 1;               // Disable pull-ups
    CMCON = 0b111;              // Disable comparator

    // Timer1 configuration
    TMR1H = 0;                  // Clear High byte Timer1 register
    TMR1L = 0;                  // Clear Low byte Timer1 register
    T1CONbits.T1CKPS = 0b11;    // Prescaler is 1:8
    TMR1CS = 0;                 // Internal clock (Fosc/4)
    TMR1ON = 1;                 // Timer1 starts to increment

    while(1) {
        if (TMR1IF) { // if TMR1 counter is overflow
            TMR1IF = 0; // Clear Timer1 overflow flag

            // Led blinking with (Fosc/4=1Mhz)/(8*65536) ~ 1.9Hz frequency
            GPIO0 = ~GPIO0;
        }
    }
}