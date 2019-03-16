#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <stdint.h>

void resetDebounce();
uint8_t debounce(uint8_t port);

#endif // #ifndef __DEBOUNCE_H__