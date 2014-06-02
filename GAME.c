#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mine/timer.h"
#include "mine/TitleScreen.h"
#include "mine/Gamer.h"



int main(void) {
	
	DDRA = 0x03; PORTA = 0xFC;
	DDRB = 0xFF; PORTB = 0x00; //selects column to display
	DDRC = 0xFF; PORTC = 0x00; //displays column pattern
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
	LCD_init();
	LCD_ClearScreen();
	TimerSet(100);
	TimerOn();
	
	unsigned char Timer_counter_Title = 0;
	const unsigned char Title_screen_period = 3;
	
	
	while(1) {
		return_value = 1;
		unsigned char button_P1_start= ~PINA&0x04;
		if(button_P1_start) //START GAME
		{
			LCD_ClearScreen();
			while(return_value)
			{
				TickFct_GAME();
				
				while (!TimerFlag); // Wait 100ms
				TimerFlag = 0;
			}
		}
	else{
		if(!(Timer_counter_Title < Title_screen_period))
		{
			LCD_ClearScreen();
			TickFct_TitleScreen();
			Timer_counter_Title = 0;
			
		}
	else{Timer_counter_Title++;}
	
}



while (!TimerFlag); // Wait 100ms
TimerFlag = 0;

    } 
}