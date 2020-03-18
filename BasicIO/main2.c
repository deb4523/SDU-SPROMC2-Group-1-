/*
 * Test Task 1.c
 *
 * Created: 01-Nov-19 10:29:52 AM
 * Author : Deborah Curtis
 */ 
#define F_CPU 16000000UL					//defines the frequency of the CPU

//include standard libraries
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

//include user libraries
#include "i2cmaster.h" 
#include "usart.h"							//to output to realterm or sdu terminal 

void turn_right(void);
void turn_left(void);
void go(void);
void reverse(void);
void stop(void);
void steppermotor(int);

int runtime;


int main(void)
{
	//configuring buttons
	DDRB = 0xFF;							//configure port b as output port
	PORTB = 0x00;							//output 0 on port b
	DDRD = 0xFF;							//configure port b as output port
	PORTD = 0x00;							//output 0 on port b
	
	i2c_init();								//initialize the communication for I2C
	uart_init();
	io_redirect();
	
	go;
	_delay_ms(10000);
	stop;
	turn_right;
	go;
	_delay_ms(3000);
	stop;
	turn_left;
	go;
	_delay_ms(10000);
	stop;
	turn_left;
	go;
	_delay_ms(3000);
	stop;
	turn_right;
	go;
	_delay_ms(10000);
	stop;
	reverse;
	stop;
	return 0;
}

void go (void){
	PIND=PIND|0b00001000;			//sets pwm output pin to 1
	PIND=PIND|0b00000100;			//sets pin d4 to 1
	PIND=PIND&0b11101111;			//sets pin d1 to 0
}

void reverse (void){
	PIND=PIND|0b00001000;			//sets pwm output pin to 1
	PIND=PIND|0b00010000;			//sets pin d4 to 1
	PIND=PIND&0b11111011;			//sets pin d1 to 0
}

void stop (void){
	PIND=PIND&0b11110111;
}

void turn_right (void){
	PORTB=0b00000011;				//AIN1, BIN1 high
	steppermotor(150);
	PORTB=0b00010000;				//h-bridge standby
}

void turn_left (void){
	PORTB=0b00001100;				//AIN2, BIN2 high
	steppermotor(150);
	PORTB=0b00010000;				//h-bridge standby
}

void steppermotor(int time){
	for (int i=0; i<time; i++){
		PIND=PIND|0b01000000;
		_delay_us(1);
		PIND=PIND|0b01100000;
		_delay_us(1);
		PIND=PIND|0b00100000;
		_delay_us(1);
		PIND=PIND|0b01100000;
		_delay_us(1);
	}
}