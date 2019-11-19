#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "utilities.h"

int main() {

	utilities_init();
	utilities_resistance();


	return 0;
}