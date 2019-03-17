/*
 * File:   counter.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>
#include "delays.h"

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTOSCIO &                // INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN.
    _WDTE_OFF &                     // Watchdog Timer disabled.
    _PWRTE_ON &                     // Power-up Timer enabled.
    _MCLRE_ON &                     // RA5/MCLR/VPP pin function is MCLR.
    _BOREN_OFF &                    // Brown-out DetecT disabled.
    _LVP_OFF &                      // RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming.
    _CP_OFF &                       // Data memory code protection off.
    _CPD_OFF;                       // Code protection off.

// Array for displaying numbers from 0 to 9
uint8_t seg[]={ 0X3F, //Hex value to display the number 0
                0X06, //Hex value to display the number 1
                0X5B, //Hex value to display the number 2
                0X4F, //Hex value to display the number 3
                0X66, //Hex value to display the number 4
                0X6D, //Hex value to display the number 5
                0X7C, //Hex value to display the number 6
                0X07, //Hex value to display the number 7
                0X7F, //Hex value to display the number 8
                0X6F  //Hex value to display the number 9
                };

int main() {
    INTCON  = 0;        // Disable interrupts

    // I/O pins configuration
    TRISA = 0;          // Port A pins are output
    PORTA = 0;
    TRISB = 0;          // Port B pins are output
    PORTB = 0;

    uint8_t clock = 0;
    uint16_t counter = 0;
    while(1) {
        if (clock == 0) {
            if (counter < 99) {
                counter++;
            } else {
                counter = 0;
            }
        }

        delay_ms(1);

        if (clock & 1) {
            PORTA = 0;
            PORTB = seg[counter % 10];
            PORTA = 0b100;
        } else {
            PORTA = 0;
            PORTB = seg[counter / 10];
            PORTA = 0b010;
        }

        clock++;
    }
}