#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

#include "display.h"
/*
unsigned char trojkat[101] = {0x19, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x08, 0x00};
unsigned char stareF[23] = {0x0b, 0xff, 0xff, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x03, 0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
unsigned char stareH[27] = {0x0d, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00};
unsigned char stareV[27] = {0x0d, 0x0f, 0x7f, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf8, 0x7f, 0x0f, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3e, 0xf0, 0xf0, 0x3e, 0x0f, 0x03, 0x00, 0x00, 0x00};
*/

unsigned char omega[31] = {0x0f, 0xe0, 0xf8, 0x3c, 0x0e, 0x06, 0x07, 0x03, 0x03, 0x07, 0x06, 0x0e, 0x3c, 0xf8, 0xe0, 0x00, 0xc1, 0xc7, 0xcf, 0xdc, 0xf8, 0xf0, 0x00, 0x00, 0xf0, 0xf8, 0xdc, 0xcf, 0xc7, 0xc1, 0x00};
unsigned char mi[21] = {0x0a, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00,0xff, 0xff, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xff, 0x7f, 0x00};

unsigned char zero[23] = {0x0b, 0xF0, 0xFC, 0x0E, 0x07, 0x03, 0x03, 0x07, 0x0E, 0xFC, 0xF0, 0x00, 0x0F, 0x3F, 0x70, 0xE0, 0xC0, 0xC0, 0xE0, 0x70, 0x3F, 0x0F, 0x00};
unsigned char one[21] = {0x0a, 0x06, 0x06, 0x03, 0x03, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00};
unsigned char two[23] = {0x0b, 0x06, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0xC6, 0xFE, 0x7C, 0x00, 0xC0, 0xE0, 0xF0, 0xD8, 0xCC, 0xCE, 0xC7, 0xC3, 0xC1, 0xC0, 0x00};
unsigned char three[23] = {0x0b, 0x06, 0x02, 0x03, 0x83, 0x83, 0x83, 0x83, 0xC6, 0x7E, 0x3C, 0x00, 0x60, 0xC0, 0xC0, 0xC1, 0xC1, 0xC1, 0xC1, 0x63, 0x7E, 0x3C, 0x00};
unsigned char four[25] = {0x0C, 0x00, 0x00, 0xC0, 0x60, 0x38, 0x0E, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x0E, 0x0F, 0x0D, 0x0C, 0x0C, 0x0C, 0x0C, 0xFF, 0xFF, 0x0C, 0x0C, 0x00};
unsigned char five[23] = {0x0B, 0x00, 0xFF, 0x7F, 0x63, 0x63, 0x63, 0xE3, 0xC3, 0xC3, 0x00, 0x00, 0x60, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0x71, 0x3F, 0x1F, 0x00};
unsigned char six[23] = {0x0B, 0xF0, 0xFC, 0x9E, 0x87, 0xC3, 0xC3, 0xC3, 0xC3, 0x86, 0x00, 0x00, 0x0F, 0x3F, 0x61, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0x7F, 0x3F, 0x00};
unsigned char seven[23] = {0x0B, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0xF3, 0x7F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x7C, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00};
unsigned char eight[23] = {0x0B, 0x3C, 0x7E, 0xC7, 0x83, 0x83, 0x83, 0x83, 0xC7, 0x7E, 0x3C, 0x00, 0x3C, 0x7E, 0xE3, 0xC1, 0xC1, 0xC1, 0xC1, 0xE3, 0x7E, 0x3C, 0x00};
unsigned char nine[23] = {0x0B, 0xFC, 0xFE, 0x87, 0x03, 0x03, 0x03, 0x03, 0x86, 0xFC, 0xF0, 0x00, 0x00, 0x61, 0xC3, 0xC3, 0xC3, 0xC3, 0xE1, 0x79, 0x3F, 0x0F, 0x00};

unsigned char F[23] = {0x0b, 0xFF, 0xFF, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0x03, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
unsigned char G[25] = {0x0c, 0xF0, 0xFC, 0x1E, 0x06, 0x03, 0x03, 0x03, 0x83, 0x83, 0x86, 0x80, 0x00, 0x0F, 0x3F, 0x78, 0x60, 0xC0, 0xC0, 0xC0, 0xC1, 0xC1, 0x7F, 0x7F, 0x00};
unsigned char H[23] = {0x0b, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0xFF, 0x00};
unsigned char M[25] = {0x0c, 0xFF, 0xFF, 0x0F, 0x7C, 0xE0, 0x00, 0xE0, 0x7C, 0x0F, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0x00};
unsigned char V[25] = {0x0c, 0x03, 0x3F, 0xFC, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x01, 0x1F, 0xFE, 0xE0, 0xFE, 0x1F, 0x01, 0x00, 0x00, 0x00};

unsigned char k[23] = {0x0b, 0xFF, 0xFF, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x30, 0x10, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x07, 0x0F, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0x00};
unsigned char m[27] = {0x0d, 0xF0, 0xF0, 0x20, 0x30, 0x30, 0xF0, 0xE0, 0x20, 0x30, 0x30, 0xF0, 0xE0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00};
unsigned char n[23] = {0x0b, 0xF0, 0xF0, 0x40, 0x20, 0x30, 0x30, 0x30, 0x70, 0xE0, 0xC0, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00};
unsigned char p[23] = {0x0b, 0xFF, 0xFF, 0x06, 0x03, 0x03, 0x03, 0x03, 0x06, 0xFE, 0xF8, 0x00, 0xFF, 0xFF, 0x03, 0x06, 0x06, 0x06, 0x06, 0x03, 0x03, 0x00, 0x00};
unsigned char u[23] = {0x0b, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x3F, 0x7F, 0xE0, 0xC0, 0xC0, 0xC0, 0x40, 0x20, 0xFF, 0xFF, 0x00};

unsigned char minus[15] = {0x07, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00};
unsigned char dot[7] = {0x03, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0x00};
unsigned char space[15] = {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char less[25] = {0x0c, 0x80, 0x80, 0xC0, 0xC0, 0x60, 0x60, 0x20, 0x30, 0x30, 0x10, 0x18, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x04, 0x0C, 0x0C, 0x08, 0x18, 0x00};
unsigned char greater[25] = {0x0c, 0x18, 0x10, 0x30, 0x30, 0x20, 0x60, 0x60, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x18, 0x08, 0x0C, 0x0C, 0x04, 0x06, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00};


unsigned char column_pointers[4] = {0x00, 0x00, 0x00, 0x00};

void display_command(unsigned char cmd) {
	/* set CS low - start a transfer */
	PORTD &=~ (1 << CS);		
	
	/* set DC low - indicates command transfer */
	PORTD &=~ (1 << DC);			
	
	/* set SCK low */
	PORTD &=~ (1 << SCK);		
	
	for (int i = 7; i >= 0; --i) {
		/* set i-th bit on the SDA*/
		if (cmd & (1 << i))
			PORTD |= (1 << SDA);
		else
			PORTD &=~ (1 << SDA);
			
		/* generate rising edge */
		PORTD ^= (1 << SCK);
		PORTD ^= (1 << SCK);
	}
	
	/* set CS high - end a transfer */
	PORTD |= (1 << CS); 		
}
void display_data(unsigned char data) {	
	/* set CS low - start a transfer */
	PORTD &=~ (1 << CS);
	
	/* set DC high - indicates data transfer */
	PORTD |= (1 << DC);
	
	/* set SCK low */
	PORTD &=~ (1 << SCK);	
	
	for (int i = 7; i >= 0; --i) {
		/* set i-th bite on the SDA*/
		if (data & (1 << i))
			PORTD |= (1 << SDA);
		else
			PORTD &=~ (1 << SDA);
			
		/* generate rising edge */
		PORTD ^= (1 << SCK);
		PORTD ^= (1 << SCK);
	}
	
	/* set CS high - end a transfer */
	PORTD |= (1 << CS); 
}
void display_clear_line(unsigned char row) {

	column_pointers[row] = 0x00;

	row *= 2;
	/* select n-th page of display */
	display_command(0xB0 | (row & 0x07));
	/* set both nibbles of RAM pointer on first column */
	display_command(0x00);
	display_command(0x10);
	
	/* clear all columns */
	for (int i = 0; i < 0x80; ++i) {
		display_data(0x00);
	}

	++row;
	/* select n-th page of display */
	display_command(0xB0 | (row & 0x07));
	/* set both nibbles of RAM pointer on first column */
	display_command(0x00);
	display_command(0x10);
	
	/* clear all columns */
	for (int i = 0; i < 0x80; ++i) {
		display_data(0x00);
	}
}
void display_clear(void) {
	for (int i = 0; i < 0x04; ++i)
		display_clear_line(i);
}
void display_clear_area(unsigned char start, unsigned char stop, unsigned char row) { //NIERUSZANE
	/* select n-th page of display */
	display_command(0xB0 | (row & 0x07));
	/* set both nibbles of RAM pointer on start column */
	display_command(start & 0x0f);
	display_command(((start >> 4) & 0x0f) | 0x10);
	
	/* clear all columns */
	for (int i = 0; i < stop - start; ++i) {
		display_data(0x00);
	}
}
void display_init(void) {
	/* set RES, SCK, SDA, CS and DC as outputs */
	DDRD |= (1 << RES) | (1 << SCK) | (1 << SDA) | (1 << CS) | (1 << DC);
	
	/* set CS high - low indicates transfer */
	PORTD |= (1 << CS);
	
	/* inital RES sequence */
	PORTD &=~(1 << RES);
	_delay_ms(10);
	PORTD |= (1 << RES);	

	/* set display on */
	display_command(0xAF);
	/* set reverse segment mapping */
	display_command(0xA1);
	/* set reverse column mapping */
	display_command(0xC8);
	/*set page adressing mode */
	display_command(0x20); display_command(0x10);
	/* set maximal contrast */
	display_command(0x81); display_command(0xff);
	
	/* clear whole display */
	for (int i = 0; i < 0x04; ++i)
		display_clear_line(i);
}	
void display_write(unsigned char character, unsigned char row) {
	unsigned char* pattern;

	switch (character) {

		case '0': {	pattern = zero; break;	}
		case '1': {	pattern = one; break;	}
		case '2': {	pattern = two; break;	}
		case '3': {	pattern = three; break;	}
		case '4': {	pattern = four; break;	}
		case '5': {	pattern = five; break;	}
		case '6': {	pattern = six; break;	}
		case '7': {	pattern = seven; break;	}
		case '8': {	pattern = eight; break;	}
		case '9': {	pattern = nine; break;	}

		case 'F': {	pattern = F; break;	}
		case 'G': {	pattern = G; break;	}
		case 'H': {	pattern = H; break;	}
		case 'M': {	pattern = M; break;	}
		case 'V': {	pattern = V; break;	}

		case 'k': {	pattern = k; break;	}
		case 'm': {	pattern = m; break;	}
		case 'n': {	pattern = n; break;	}
		case 'p': {	pattern = p; break;	}
		case 'u': {	pattern = u; break;	}
		
		case '-': {	pattern = minus; break;		}
		case '.': {	pattern = dot; break;		}
		case ' ': {	pattern = space; break;		}
		case '<': {	pattern = less; break;		}
		case '>': {	pattern = greater; break;	}

		case 'R': {	pattern = omega; break;		}
		case 'q': {	pattern = mi; break;		}

		default:  { pattern = 0x00;	}
	};

	if (pattern != 0x00) {
		char character_length = *pattern++;
	
		for (int r = 0; r < 2; ++r) {
			/* select n-th page of display */
			display_command(0xB0 | ((2 * row + r) & 0x07));
			/* set RAM pointer on desired column */
			display_command(column_pointers[row] & 0x0f);
			display_command(((column_pointers[row] >> 4) & 0x0f) | 0x10);

			for (int length = 0; length < character_length; ++length) {
				display_data(*pattern);
				++pattern;
			}
		}
		column_pointers[row] += character_length;
	}	
}
void display_write_number(long long number, unsigned char row) {
	/* count number's digits */
	char cnt = 0;
	int temp = number;
	while (temp) {
		++cnt;
		temp /= 10;
	}
	
	if (number < 0) {
		display_write('-', row);
		number *= -1;
	}
	if (cnt < 2) 
		display_write('0' + number, row);
	else {
		char digits[5] = {0, 0, 0, 0, 0};
		for (int i = cnt - 1; i >= 0; --i) {
			digits[i] = number % 10;
			number /= 10;
		}
		
		int i = 0;
		while (*(digits + i) == 0)
			++i;
	
		for (; i < cnt; ++i)
			display_write('0' + digits[i], row);
	}	
}
void display_write_double(double number, unsigned char precision, unsigned char row) {
	if (number < 0) {
		display_write('-', row);
		number *= -1;
	}

	display_write_number((int)number, row);
	display_write('.', row);

	while (precision--) {
		number -= (int)number;
		number *= 10;
		display_write('0' + (int)number, row);
	}
}
