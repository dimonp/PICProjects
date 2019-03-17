/*
 * File:   blink.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTOSCIO &                // INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN.
    _WDTE_OFF &                     // Watchdog Timer disabled.
    _PWRTE_ON &                     // Power-up Timer enabled.
    _MCLRE_ON &                     // RA5/MCLR/VPP pin function is MCLR.
    _BOREN_OFF &                    // Brown-out DetecT disabled.
    _LVP_OFF &                      // RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming.
    _CP_OFF &                       // Data memory code protection off.
    _CPD_OFF;                       // Code protection off.

int main() {
    INTCON  = 0;        // Disable interrupts

    // I/O pins configuration
    TRISA = 0;          // All pins are output

    uint16_t counter = 0;
    while(1) {
        PORTA = (counter >> 12) & 0b111;
        counter++;
    }
}