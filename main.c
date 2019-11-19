#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "utilities.h"

int main() {

	utilities_init();
	display_write('.', 3);
	// check for selected resistance 
	int inner_resistance = R150_selected() ? 150 : 10000;
display_write('<', 3);
	//set CIRCUIT_POWER_SWITCH as an low output and wait for circuit to discharge
	DDRD |= (1 << CIRCUIT_POWER_SWITCH);	
	while (ADC_unipolar_measurement(1) > 0) 
		continue;
	display_write_number(0, 3);


	// enable analog comparator multiplexer
	SFIOR |= (1 << ACME);
	// clears ADC input selection
	ADMUX &= 0xf0; 
	// chooses desired input
	ADMUX |= 1; 
display_write_number(1, 3);
	// enable interrupts
	sei();
	// enable analog comparator interrupt
	ACSR |= (1 << ACIE);
	
	unsigned int rising_half_charge_time;
	unsigned int falling_half_charge_time;

	// power the circuit on
	PORTD |= (1 << CIRCUIT_POWER_SWITCH);
	TCCR1B |= (1 << CS10);
display_write_number(2, 3);
	while (TCCR1B & (1 << CS10))
		continue;
	display_write_number(3, 3);
	rising_half_charge_time = TCNT1;
	TCNT1 = 0;

	display_write_number(rising_half_charge_time, 0);





	return 0;
}

ISR(ANA_COMP_vect) {
	// stop timer1
	TCCR1B &=~ (1 << CS10);
	display_write_number(77777, 2);
}