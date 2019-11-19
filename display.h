#ifndef _display_H
#define _display_H

// PORTD is for digital outputs
#define SCK	PD2
#define SDA	PD3
#define RES	PD4
#define DC	PD5
#define CS	PD6

void display_command(unsigned char cmd);
void display_data(unsigned char data);
void display_clear_line(unsigned char row);
void display_clear(void);
void display_clear_area(unsigned char start, unsigned char stop, unsigned char row);
void display_init(void);
void display_write(unsigned char character, unsigned char row);
void display_space(int width, unsigned char row);
void display_write_number(long long number, unsigned char row);
void display_write_double(double number, unsigned char precision, unsigned char row);

#endif