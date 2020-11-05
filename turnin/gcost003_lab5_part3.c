/*	Author: Giovanni Costagliola
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait, incPress, incRelease, decPress, decRelease} state;

unsigned char B1,  tempB = 0;
unsigned char cnt = 0;
unsigned char flip = 0;

void LED_On() {
	B1 = ~PINA & 0x01;

	switch(state){
		case Start:	state = Wait;
				break;
		case Wait:	if(flip == 0 && B1 == 1){
					state = incPress;
					cnt++;
				}
				else if(flip == 1 && B1 == 1){
					state = decPress;
					cnt++;
				}
				else {
					state = Wait;
				}
				break;
		case incPress:	state = incRelease;
				break;
		case incRelease:	if(B1 == 0){
					if(cnt > 7){
						flip = 1;
						cnt = 0;
					}
					state = Wait;
				}
				else {
					state = incRelease;
				}
				break;
		case decPress:	state = decRelease;
				break;
		case decRelease:	if(B1 == 0){
					if(cnt > 7){
						flip = 0;
						cnt = 0;
					}
					state = Wait;
				}
				else {
					state = decRelease;
				}
				break;
		default:	break;
	}

	switch(state){
		case Start:	
				tempB = 0;
				break;
		case Wait:	
				break;
		case incPress:	
				tempB = 0x01 << (cnt - 1);
				break;
		case incRelease:	
				break;
		case decPress:	
				tempB = 0x01 << (7 - cnt);
				break;
		case decRelease:	
				break;
		default:	
				break;
	}
    PORTB = tempB;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	
	state = Start;
    /* Insert your solution below */
    while (1) {
	LED_On();
	//PORTB = tempB;
	
    }
    return 1;
}
