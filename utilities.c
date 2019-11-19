#include "utilities.h"
#include "display.h"
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

const int ADC_MEASUREMENT_AVERAGING_LEVEL = 4;

void utilities_init(void) {
	//enable display
	display_init();
	
}
double ADC_unipolar_measurement(int input) {
	// enable ADC
	ADCSRA |= (1 << ADEN);
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);
	_delay_ms(50);
	// clears ADC input selection
	ADMUX &= 0xf0; 
	// chooses desired input
	ADMUX |= input; 

	int results = 0.0;
	for (int i = 0; i < ADC_MEASUREMENT_AVERAGING_LEVEL; ++i) {
		
		//performs a measurement
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC))
			continue;

		results += ADC;
	}
	
	// disable ADC
	ADCSRA &=~ (1 << ADEN);

	return results / ADC_MEASUREMENT_AVERAGING_LEVEL;
}
int R150_selected(void) {	
	//set CIRCUIT_POWER_SWITCH as an low output and wait for circuit to discharge
	DDRD |= (1 << CIRCUIT_POWER_SWITCH);	
	while (ADC_unipolar_measurement(1) > 0) 
		continue;

	// set CIRCUIT_DISCHARGE_SWITCH as an low output
	DDRD |= (1 << CIRCUIT_DISCHARGE_SWITCH);	

	// power the circuit on and wait for complete execution
	PORTD |= (1 << CIRCUIT_POWER_SWITCH);
	while (!(PIND & (1 << CIRCUIT_POWER_SWITCH)))
		continue;

	// check the state of RESISTOR_SELECT_SIGNAL
	int _R150_selected = PINA & (1 << RESISTOR_SELECT_SIGNAL) ? 0 : 1;

	// undo changes made
	PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);
	DDRD &=~ (1 << CIRCUIT_POWER_SWITCH);
	DDRD &=~ (1 << CIRCUIT_DISCHARGE_SWITCH);

	return _R150_selected;
}
double resistance_measurement(int inner_resistance) {
	// power the circuit on and wait for complete execution
	DDRD |= (1 << CIRCUIT_POWER_SWITCH);
	PORTD |= (1 << CIRCUIT_POWER_SWITCH);
	while (!(PIND & (1 << CIRCUIT_POWER_SWITCH)))
		continue;

	double component_voltage = ADC_unipolar_measurement(1);
	double circuit_power_voltage = ADC_unipolar_measurement(6);

	// power the circuit off
	PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);
	DDRD &=~ (1 << CIRCUIT_POWER_SWITCH);

	return (component_voltage * inner_resistance) / (circuit_power_voltage - component_voltage);
}
void utilities_resistance(void) {
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
			_delay_ms(100);
		}

		temp = curr;
		inner_resistance = R150_selected() ? 150 : 10000;
		curr = resistance_measurement(inner_resistance);
	}
}
void capacitance_measurement(int inner_resistance) {

}
void inductance_measurement(void) {

}
void voltage_measurement(void) {

}