/* 
 * delay for d microseconds on a 4Mhz clock
 */

#include <stdint.h>

/* delay for d milliseconds
 * 0 < d < 255
 * Trashes W 
 */
uint8_t loop2;
uint8_t loop1;
void delay_ms(uint8_t d) {
    loop1 = d;

    __asm__("               \n \
    _DELAY_1:               \n \
        movlw 110           ; close to 1.0 msec delay when set to .110  \n \
        movwf _loop2        \n \
    _DELAY_2:               \n \
        nop                 \n \
        nop                 \n \
        nop                 \n \
        nop                 \n \
        nop                 \n \
        nop                 \n \
        decfsz  _loop2, F   ; decrement and leave result in LOOP2       \n \
                            ; skip next statement if zero               \n \
        goto $-7            ; goto _DELAY_2                             \n \
        decfsz  _loop1, F                                               \n \
        goto $-0xb          ; goto _DELAY_1                             \n \
    ");
}

/* delay for d*10 milliseconds 
   * 0 < d < 255
*/
void delay_ms10(uint8_t d) {
    for(uint8_t i=0; i < d; i++) {
        delay_ms(100);
    }
}
