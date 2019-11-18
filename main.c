#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "utilities.h"

int main() {

	utilities_init();
	int inner_resistance = R150_selected() ? 150 : 10000;
	double curr = resistance_measurement(inner_resistance);
	double temp = 0;


	while (1) {
		
		if (curr != temp) {
			display_clear_line(0);
			if (inner_resistance == 150) {
				display_write_double(curr, 1, 0);
				display_write(' ', 0);
				display_write('R', 0);
			} else {
				display_write_double(curr / 1000.0, 3, 0);
				display_write(' ', 0);
				display_write('k', 0);
				display_write('R', 0);
			}
			_delay_ms(50);
		}

		temp = curr;
		inner_resistance = R150_selected() ? 150 : 10000;
		curr = resistance_measurement(inner_resistance);
	}


	return 0;
}