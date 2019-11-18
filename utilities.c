#include "utilities.h"
#include "display.h"
#include <avr/io.h>

const int ADC_MEASUREMENT_AVERAGING_LEVEL = 4;

void utilities_init(void) {
	//enable display
	display_init();
	//enable ADC
	ADCSRA |= (1 << ADEN);
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);
	
}
double ADC_unipolar_measurement(int input) {
	ADMUX &= 0xf0; //clears ADC input selection
	ADMUX |= input; //chooses desired input

	int results = 0.0;
	for (int i = 0; i < ADC_MEASUREMENT_AVERAGING_LEVEL; ++i) {
		
		//performs a measurement
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC))
			continue;

		results += ADC;
	}
	
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
void capacitance_measurement(void) {

}
void inductance_measurement(void) {

}
void voltage_measurement(void) {

}