#ifndef _UTILITIES_H
#define _UTILITIES_H

// PORTA is for analog and digital inputs
#define RESISTOR_SELECT_SIGNAL		PA7

// PORTD is for digital outputs
#define	CIRCUIT_POWER_SWITCH		PD1
#define	CIRCUIT_DISCHARGE_SWITCH	PD0

void utilities_init(void);
double ADC_unipolar_measurement(int input);
int R270_selected(void);
double resistance_measurement(int inner_resistance);
void utilities_resistance(void);
void capacitance_measurement(int inner_resistance);
void inductance_measurement(void);
void voltage_measurement(void);



#endif