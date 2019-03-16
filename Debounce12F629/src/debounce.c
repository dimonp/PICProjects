#include <stdint.h>

#define FINAL_COUNT 500

uint16_t count = 0;

void resetDebounce() {
	count = 0;
}

uint8_t debounce(uint8_t port) {
	if (port == 0) {
		if (count < UINT16_MAX) {
			count++;
		}
	}

	if (count > FINAL_COUNT && port == 1) {
		return 1;
	}

	return 0;
}
