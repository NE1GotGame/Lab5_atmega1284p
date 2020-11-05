/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
   
    unsigned char tempA, level;
    
    /* Insert your solution below */
    while (1) {

	level = 0x00;
	tempA = ~PINA & 0x0F;
	if(tempA <= 4){
		level = 0x40;
	}
	else{
		level = 0x00;
	}
	if(tempA == 0x01 || tempA == 0x02){
		level = level | 0x20;
	}
	else if(tempA == 3 || tempA == 4){
		level = level | 0x30;
	}
	else if(tempA == 5 || tempA == 6){
		level = 0x38;
	}
	else if(tempA >= 7 && tempA <= 9){
		level = level | 0x3C;
	}
	else if(tempA >= 10 && tempA <= 12){
		level = level |	0x3E;
	}
	else if(tempA >= 13 && tempA <= 15){
		level = level | 0x3F;
	}
	PORTC = level;
   }	
   return 1;
}

