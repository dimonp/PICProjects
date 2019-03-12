/*
 * File:   blink.c
 */

#include <stdint.h>
#include <pic16fam.h>
#include <pic16regs.h>
#include <sdcc-lib.h>

uint16_t __at(_CONFIG) __CONFIG = 
    _FOSC_INTRCCLK & 
    _WDTE_OFF & 
    _PWRTE_ON & 
    _MCLRE_ON & 
    _BOREN_OFF & 
    _CP_OFF & 
    _CPD_OFF;

void delay_ms(char d);
void delay_ms10(char d);

int main() {
    // calibrate internal oscillator
    __asm__("             \n \
        call 0x03ff       \n \
        bsf STATUS,RP0    \n \
        movwf OSCCAL      \n \
        bcf STATUS, RP0   \n \
    ");

    TRISIO = 0;               // all pins are output
    GPIO = 0;                 // Make all pins 0
    NOT_GPPU = 1;
    
    while(1) {
        GPIO = 0b001;
        delay_ms10(5);

        GPIO = 0b010;
        delay_ms10(5);

       GPIO = 0b100;
       delay_ms10(5);
    }
}