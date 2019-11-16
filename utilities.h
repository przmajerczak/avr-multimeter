#ifndef _UTILITIES_H
#define _UTILITIES_H

// PORTA is for analog and digital inputs
#define RESISTOR_SELECT_SIGNAL		PA7
#define	COMPONENT_DISCHARGE_SIGNAL	PA6

// PORTD is for digital outputs
#define COMPONENT_DISCHARGE_SWITCH	PD7
#define	CIRCUIT_POWER_SWITCH		PD1

double ADC_unipolar_measurement(int measures);
void utilities_init(void);
void resistance_measurement(void);
void capacitance_measurement(void);
void inductance_measurement(void);
void voltage_measurement(void);

#endif