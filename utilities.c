#include "utilities.h"
#include "display.h"
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int ADC_MEASUREMENT_AVERAGING_LEVEL = 4;
const int DISCHARGE_THRESHOLD = 0;
const long long TIMER1_CYCLE_DURATION_us = 65536 / (F_CPU / 1000000);
const long long TIMER1_COUNT_DURATION_us = 1 / (F_CPU / 1000000);
int timer1_cycles;

void utilities_init(void) {
	//enable display
	display_init();
	// enable ADC
	ADCSRA |= (1 << ADEN);
	// set AVCC as reference voltage
	ADMUX |= (1 << REFS0);
}
double ADC_unipolar_measurement(int input) {
	//_delay_ms(50);
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
	//ADCSRA &=~ (1 << ADEN);

	return results / ADC_MEASUREMENT_AVERAGING_LEVEL;
}
int R270_selected(void) {	
	//set CIRCUIT_POWER_SWITCH as an low output and wait for circuit to discharge
	PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);	
	while (ADC_unipolar_measurement(1) > DISCHARGE_THRESHOLD) 
		continue;

	// set CIRCUIT_DISCHARGE_SWITCH as an low output
	DDRD |= (1 << CIRCUIT_DISCHARGE_SWITCH);	

	// power the circuit on and wait for complete execution
	PORTD |= (1 << CIRCUIT_POWER_SWITCH);
	while (!(PIND & (1 << CIRCUIT_POWER_SWITCH)))
		continue;

	// check the state of RESISTOR_SELECT_SIGNAL
	int _R270_selected = PINA & (1 << RESISTOR_SELECT_SIGNAL) ? 0 : 1;

	// undo changes made
	PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);
	//DDRD &=~ (1 << CIRCUIT_POWER_SWITCH);
	DDRD &=~ (1 << CIRCUIT_DISCHARGE_SWITCH);

	return _R270_selected;
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
	int inner_resistance = R270_selected() ? 270 : 10000;
	double curr = resistance_measurement(inner_resistance);
	double temp = 0;

	while (1) {
		
		if (curr != temp) {
			display_clear_line(0);
			if (inner_resistance == 270) {
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
		inner_resistance = R270_selected() ? 270 : 10000;
		curr = resistance_measurement(inner_resistance);
	}
}
void capacitance_measurement(int inner_resistance) {
	long long half_charge_time_ns;
	timer1_cycles = 0;
	TCNT1 = 0;
	// enable interrupts
	sei();
	//set CIRCUIT_POWER_SWITCH as an low output and wait for circuit to discharge
	PORTD &=~ (1 << CIRCUIT_POWER_SWITCH);	
	while (ADC_unipolar_measurement(1) > DISCHARGE_THRESHOLD) 
		continue;
	// power the circuit on
	PORTD |= (1 << CIRCUIT_POWER_SWITCH);
	// start timer1, wait for analog comparator's interrupt occur and turn it off
	TCCR1B |= (1 << CS10);
	while (TCCR1B & (1 << CS10))
		continue;
	// disable interrupts
	cli();

	half_charge_time_ns = 1000 * (timer1_cycles * TIMER1_CYCLE_DURATION_us + TCNT1 * TIMER1_COUNT_DURATION_us);
	double capacitance = half_charge_time_ns / (0.7 * inner_resistance);
	char prefix;
	if (capacitance < 0) {
		prefix = 'p';
		capacitance *= 1000;
	} else if (capacitance > 1000000) {
		prefix = 'm';
		capacitance /= 1000000;
	} else if (capacitance > 1000) {
		prefix = 'u';
		capacitance /= 1000;
	} else
		prefix = 'n';
	display_clear_line(0);
	display_write_double(capacitance, 1, 0);
	display_write(' ', 0);
	display_write(prefix, 0);
	display_write('F', 0);
	
	

}
void inductance_measurement(void) {

}
void voltage_measurement(void) {

}

ISR(ANA_COMP_vect) {
	// stop timer1
	TCCR1B &=~ (1 << CS10);
}

ISR(TIMER1_OVF_vect) {
	++timer1_cycles;
}