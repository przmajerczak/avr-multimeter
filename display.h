#ifndef _display_H
#define _display_H

//definiować tu też port na później
#define SCK	PB0
#define SDA	PB1
#define RES	PB2
#define DC	PB3
#define CS	PB4	

void display_command(unsigned char cmd);
void display_data(unsigned char data);
void display_clear_line(unsigned char row);
void display_clear(void);
void display_clear_area(unsigned char start, unsigned char stop, unsigned char row);
void display_init(void);
void display_write(unsigned char character, unsigned char row);
void display_space(int width, unsigned char row);
void display_write_number(int number, unsigned char row);
void display_write_double(double number, unsigned char precision, unsigned char row);

#endif