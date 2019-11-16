#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "utilities.h"

int main() {

	





	utilities_init();
	while (1) {
		display_clear_line(0);
		
		display_write_double(ADC_unipolar_measurement(10), 2, 0);
		_delay_ms(100);

	}


	return 0;
}