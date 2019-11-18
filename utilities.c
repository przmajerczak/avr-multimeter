#include "utilities.h"
#include "display.h"
#include <avr/io.h>


double ADC_unipolar_measurement(int measures) {
	ADMUX &= 0xf0; //clears ADC input selection
	ADMUX |= (1 << MUX0); //chooses ADC1 input

	int results = 0.0;
	for (int i = 0; i < measures; ++i) {
		
		//perform a measurement
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC))
			continue;

		results += ADC;
	}
	
	return results / measures;
}
int R150_selected(void) {	
	//set CIRCUIT_POWER_SWITCH as an low output and wait for circuit to discharge
	DDRD |= (1 << CIRCUIT_POWER_SWITCH);	
	while (ADC_unipolar_measurement(4) > 0) 
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
	DDRD &=~ (1 << CIRCUIT_POWER_SWITCH) | (1 << CIRCUIT_DISCHARGE_SWITCH);

	return _R150_selected;
}
void utilities_init(void) {
	//enable display
	display_init();
	//enable ADC
	ADCSRA |= (1 << ADEN);
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);
	
}
void resistance_measurement(void) {
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);
	
	int inner_resistance;
	if (R150_selected() == 1)
		inner_resistance = 150;
	else
		inner_resistance = 10000;

	double component_voltage = ADC_unipolar_measurement(8);

	display_write_double((component_voltage * inner_resistance) / (1023.0 - component_voltage), 2, 0);
	display_write('R', 0);
	display_write_number(inner_resistance, 2);
	display_write_double(component_voltage, 2, 3);


	// power the circuit off
	//PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);
}
void capacitance_measurement(void) {

}
void inductance_measurement(void) {

}
void voltage_measurement(void) {

}