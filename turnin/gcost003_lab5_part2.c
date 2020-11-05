/*	Author: Giovanni Costagliola
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, increase, decrease, reset, wait1, wait2}state;

unsigned char Button1;
unsigned char Button2;
unsigned char tmpC;


void LED_ON(){
	Button1 = ~PINA & 0x01;
	Button2 = ~PINA & 0x02;

	switch (state){

		case init:
			if(!Button1 && !Button2){
				state = init;
			}
			else if(Button1 && !Button2){
				state = increase;
			}
			else if(!Button1 && Button2){
				state = decrease;
			}
			else{
				state = reset;
			}

			break;
		case increase:
			if(Button1 && Button2){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;
		case decrease:
			if(Button1 && Button2)
			{
				state = reset;
			}
			else{
				state = wait2;
			}
			break;

		case reset:
			if(!Button1 && !Button2){
				state = init;
			}
			else if(Button1 && !Button2){
				state = decrease;
			}
			else if(Button1 && Button2){
				state = reset;
			}
			break;


		case wait1:
			if(Button1 && Button2){
				state = reset;
			}
			else if(Button1 && !Button2){
				state = increase;
			}
			else if(!Button1 && Button2){
				state = decrease;
			}
			else{
				state = wait1;
			}
			break;
		case wait2:
			if(!Button1 && !Button2){
				state = wait1;
			}
			else if(Button1 && Button2){
				state = reset;
			}
			else{
				state = wait2;
			}
			break;

	}
	switch(state){
		case init:
			break;
		case increase:
			if(tmpC < 9){
				tmpC += 0x01;
			}
			break;
		case decrease:
			if(tmpC > 0){

				tmpC -= 0x01;
			}
			break;
		case reset:
			tmpC = 0x00;
			break;
        	case wait1:
        	case wait2:
            		break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */

    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */


    state = init;
    tmpC = 0x07;
    //unsigned char tmpC = 0x07;
    while (1) {
	LED_ON();
	PORTC = tmpC;
    }
    return 1;
}

