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


int main(void)
{
	i2c_init();								//initialize the communication for I2C
	uart_init();
	io_redirect();
	
	
	//configuring buttons
	DDRB = 0xFF;							//configure port b as output port
	PORTB = 0x00;							//output 0 on port b
	DDRD = 0xFF;							//configure port b as output port
	PORTD = 0x00;							//output 0 on port b
	
	int runtime = 5;
	go();										//starts motor goes straight
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
		}										//motor run time (5 sec)
	stop();										//stop motor
	_delay_ms(1000);
	
	turn_right();								//turns front wheel to the right
	runtime=3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}//_delay_ms(3000);							//motor run time (3 sec)
	stop();										//stops motor
	
	go();										//starts motor - goes right
	runtime=3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}//_delay_ms(3000);							//motor run time (3 sec)
	stop();										//stops motor
	_delay_ms(1000);
	
	turn_left();								//turns front wheel straight
	runtime=3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}//_delay_ms(3000);							//motor run time (3 sec)
	stop();										//stops motor
	
	go();										//starts motor - goes straight
	runtime = 5;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}											//motor run time (5 sec)
	stop();										//stop motor
	_delay_ms(1000);
	
	turn_left();								//turns front wheel left
	runtime=3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}//_delay_ms(3000);							//motor run time (3 sec)
	stop();										//stops motor
	
	go();										//starts motor - goes left	
	runtime = 3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}											//motor run time (3 sec)
	stop();										//stop motor
	//_delay_ms(1000);
	
	turn_right();								//turns front wheel straight
	runtime=3;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}//_delay_ms(3000);							//motor run time (3 sec)
	stop();										//stops motor
	
	go();										//starts motor - goes straight
	runtime = 5;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}											//motor run time (5 sec)
	stop();										//stop motor
	_delay_ms(1000);
	
	reverse();									//motor reverses
	runtime = 5;
	for (int j=1; j<=runtime; j++){
		_delay_ms(1000);
		printf("%d  \n", j);
	}											//motor run time (5 sec)
	stop();										//stop motor
	
	return 0;
}

void go (void){
	printf("go \n");
	PORTD=PORTD|0b00001000;			//sets pwm output pin to 1
	PORTD=PORTD|0b10000000;			//sets d7 pin to 1 (h-bridge standby)
	PORTD=PORTD|0b00000100;			//sets pin d2 to 1
	PORTD=PORTD&0b11101111;			//sets pin d4 to 0
}

void reverse (void){
	printf("reverse \n");
	PORTD=PORTD|0b00001000;			//sets pwm output pin to 1
	PORTD=PORTD|0b10000000;			//sets d7 pin to 1 (h-bridge standby)
	PORTD=PORTD|0b00010000;			//sets pin d4 to 1
	PORTD=PORTD&0b11111011;			//sets pin d2 to 0
}

void stop (void){
	printf("stop \n");
	PORTD=PORTD&0b11100011;			//sets pwm output pin, d2, d4 to 0
	PORTD=PORTD&0b01111111;			//sets d7 pin to 0 (h-bridge standby)
	PORTD=PORTD&0b11001111;			//sets pwm output pin to 0
	PORTB=0b00000000;				//h-bridge standby
}

void turn_right (void){
	printf("right \n");
	PORTD=PORTD|0b00100000;			//sets pwm output pin to 1
	//PORTB=0b00010000;				//
	PORTD=PORTD|0b10000000;			//sets d7 pin to 1 (h-bridge standby)
	PORTB=0b00000100;				//BIN1 high
	//steppermotor(1000);			//starts pwm to stepper motor
	//PORTB=0b00000000;				//h-bridge standby
}

void turn_left (void){
	printf("left \n");
	PORTD=PORTD|0b00100000;			//sets pwm output pin to 1
	//PORTB=0b00010000;				//h-bridge standby
	PORTD=PORTD|0b10000000;			//sets d7 pin to 1 (h-bridge standby)
	PORTB=0b00010010;				//BIN2 high
	//steppermotor(1000);			//starts pwm to stepper motor
	//PORTB=0b00000000;				//h-bridge standby
}

/*void steppermotor(int time){
	PORTD=PORTD&0b10011111;			//sets pins d5 & d6 to 0
		//PORTD=PORTD|0b01000000;		//sets pin d6 to 1
		//time=time*1000;
	for (int i=0; i<time; i++){		//for loop will repeat 'time' times
		for (int j=0; j<time; j++){}
		PORTD=PORTD|0b01100000;		//sets pins d5 and d6 to high
		_delay_us(1);
		PORTD=PORTD&0b10111111;		//sets pin d6 to 0
		_delay_us(1);
		PORTD=PORTD|0b01100000;		//sets pins d5, d6 to high
		_delay_us(1);		
		PORTD=PORTD&&0b11011111;		//sets pin d5 to 0
		_delay_us(1);				
		}
	PORTD=PORTD&0b10011111;
}*/