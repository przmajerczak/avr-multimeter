#include "utilities.h"
#include "display.h"
#include <avr/io.h>


double ADC_unipolar_measurement(int measures) {
	//measures unipolar voltage on ADC1 pin
	ADMUX &= 0xf0; //clears ADC input selection
	ADMUX |= (1 << MUX0); //choosezs ADC1 input

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
void utilities_init(void) {
	display_init();
		//enable ADC
	ADCSRA |= (1 << ADEN);
}
void resistance_measurement(void) {
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);

	


}
void capacitance_measurement(void) {

}
void inductance_measurement(void) {

}
void voltage_measurement(void) {

}