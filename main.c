#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

int main() {




	display_init();
	
	while(1)
		;

	return 0;
}