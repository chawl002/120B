#ifndef __Gamer_h__
#define __Gamer_h__

#include <io.h>
#include "mine/Matrix.h"

unsigned char *correct_easy[] = {"usually", "even", "understood", "blank", "Sunday", "dancer", "curves", "futuristic", "noisy", "December", "mischievous"};
unsigned char *incorrect_easy[] = {"thier", "galaxi", "woory", "erorr", "aquire", "amature", "colum", "ignorence", "mideval", "miniture", "occurence"};
unsigned char *word_pattern[] = {1, 10, 2, 7, 3, 4, 8, 5, 9, 6, 0, 1};
unsigned char *word_correct_pattern[] = {0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,0,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,0,0};
//88 total, used for correct/incorrect array choices
unsigned char arraysize = 10; // the amount of words in in/correct array

unsigned char wait_two_seconds = 20;
	unsigned char player = 1;
	unsigned char p_i = 0; //player iterator for time
	unsigned char e_i = 0; //end of round iterator for time
	unsigned char m_i = 0; //Matrix iterator to slow it down
	const unsigned char matrix_tick_time = 3;
	//unsigned char turn = 0;
	//unsigned char level = 1;
	unsigned char word_correctness = 0;  //determines is a correctly spelled word shall appear
	unsigned char word_choice = 0; //chooses a word from an array
	unsigned char wc_i = 0; //iterators for word choice function
	unsigned char wc_j = 0;
	unsigned char score = 0; //keeps score for that round
	unsigned char score_tens = 0; //if it goes over 9
	unsigned char mistake_counter = 0; //counts # of mistakes - every 3 mistakes you lose round early
	unsigned char total_score_P1 = 0;
	unsigned char total_score_tens_P1 = 0;
	unsigned char total_score_P2 = 0;
	unsigned char total_score_tens_P2 = 0;
	int matrix_timer = 0;
//	 unsigned char return_value = 1;
//	unsigned char random_number = 0;
	
enum G_States { G_GAME_START, G_switchplayer, G_pickwordchoice, G_decide, G_correct_word, G_incorrect_word, G_correct_button, G_incorrect_button, G_switchplayer_message } G_State;

TickFct_GAME() {
	//Buttons for Player 1 //
	unsigned char button_P1_incorrect= ~PINA&0x08;
	unsigned char button_P1_correct= ~PINA&0x04;
	//Buttons for player 2//
	unsigned char button_P2_correct = ~PINA&0x20;
	unsigned char button_P2_incorrect = ~PINA&0x10;
	
	switch(G_State) { // Transitions
	case -1:
	G_State = G_GAME_START; 
	break;
	case G_GAME_START:  //Starts Game
	if (1) {
		G_State = G_switchplayer;
	}
	break;
	
	case G_switchplayer: //Switches between the two players
	if(p_i < wait_two_seconds)  //STAY HERE UNTIL 2 SECOND PASSES
	{
		p_i++;
		G_State = G_switchplayer;
	}		
	else if(!(p_i < wait_two_seconds)) //WHEN SWITCHING TO GAMEPLAY, SWAP PLAYER FOR NEXT INTERATION
	{
		p_i = 0;
			score = 0;
			score_tens = 0;
		G_State = G_pickwordchoice;
	}		
	break;
	
	case G_pickwordchoice: //Choose if the word will be misspelled or not
	G_State = G_decide;
	break;
	
	case G_decide: //Output Word and Score to Screen //Start timer
	if (word_correctness) {
		G_State = G_correct_word;
	}
	else if(!word_correctness){
		G_State = G_incorrect_word;
	}
	break;
	
	case G_correct_word: //Wait for button response
	if(player == 1)
	{
		if (!button_P1_correct && !button_P1_incorrect) {   //if no buttons pressed, do nothing
		G_State = G_correct_word;
		}				
	
		else if (button_P1_correct) { //Correct word and correct button pressed
			G_State = G_correct_button;
		}
		else if(button_P1_incorrect) //Correct word and incorrect button pressed
		{
			G_State = G_incorrect_button;
		}
	}	
	else if(player == 2)
	{
		if (!button_P2_correct && !button_P2_incorrect) {   //if no buttons pressed, do nothing
			G_State = G_correct_word;
			}
			
			else if (button_P2_correct) { //Correct word and correct button pressed
			G_State = G_correct_button;
		}
		else if(button_P2_incorrect) //Correct word and incorrect button pressed
		{
			G_State = G_incorrect_button;
		}
	}
	break;
	
	case G_incorrect_word:
	if(player == 1)
	{
		if(!button_P1_correct && !button_P1_incorrect) //incorrect word and correct button pressed
		{
			G_State = G_incorrect_word;
		}
		else if (button_P1_correct) //incorrect word and correct button
		{ 
			G_State = G_incorrect_button;
		}
		else if(button_P1_incorrect)
		{
			G_State = G_correct_button;
		}
	}	
		if(player == 2)
		{
			if(!button_P2_correct && !button_P2_incorrect) //incorrect word and correct button pressed
			{
				G_State = G_incorrect_word;
			}
			else if (button_P2_correct) //incorrect word and correct button
			{
				G_State = G_incorrect_button;
			}
			else if(button_P2_incorrect)
			{
				G_State = G_correct_button;
			}
		}	
	break;
	
	case G_correct_button: //Add 1 to score
	if(1)
	{
		G_State = G_pickwordchoice;
	}	
	break;
	
	case G_incorrect_button: //Count # of mistakes. if too many, switch player
	if(mistake_counter < 3)
	{
		G_State = G_pickwordchoice;
	}		
	else if(!(mistake_counter < 3))
	{

		G_State = G_switchplayer_message;
	}
	break;
	
	case G_switchplayer_message:
	
	if(!(e_i < wait_two_seconds)) //swap players and send to player screen
	{
		if(player == 1)
		{
			player = 2;
		}
		else if(player == 2)
		{
			player = 1;
		}
		e_i = 0;
		G_State = G_switchplayer;
	}
	else if(e_i < wait_two_seconds) //Wait here for 2 seconds
	{
		e_i++;
		G_State = G_switchplayer_message;
	}
	break;
	
	default:
	G_State = G_GAME_START;
} // Transitions





switch(G_State) { // State actions
case G_GAME_START:
break;

case G_switchplayer:
		mistake_counter = 0;
if(player == 1 && p_i == 0)
{
	
	//matrix_timer = Matrix_Tick(-1); //TIMER RESET?
	//Display p1 total score
	LCD_ClearScreen();
	LCD_DisplayString(1, "Player 1: ");
	LCD_Cursor(12);
	LCD_WriteData(total_score_tens_P1 + '0');
	LCD_Cursor(13);
	LCD_WriteData(total_score_P1 + '0');

}
else if(player == 2 && p_i == 0)
{ 
	//matrix_timer = Matrix_Tick(-1); //TIMER RESET?
	//Display p2 total score
	LCD_ClearScreen();
	LCD_DisplayString(1, "Player 2: ");
	LCD_Cursor(12);
	LCD_WriteData(total_score_tens_P2 + '0');
	LCD_Cursor(13);
	LCD_WriteData(total_score_P2 + '0');
}

Matrix_Tick(-1);

break;

case G_pickwordchoice:
	word_correctness = word_correct_pattern[wc_j];
	if(wc_j < 88)
	{
		wc_j++;
	}
	else
	{
		wc_j = 0;
	}
/*choose if in/correct*/
break;

case G_decide:
LCD_ClearScreen();

word_choice = word_pattern[i];     //"Randomly" generated words array
if(word_correctness)
{
	LCD_DisplayString(1, correct_easy[word_choice]); //Displays word
}
else if(!word_correctness)
{
	LCD_DisplayString(1, incorrect_easy[word_choice]); //Displays word
}

//SCORE OUTPUT MIDGAME
if(!(score < 10)) //OUPTPUT VALUES GREATER THAN 9
{
	score = score - 10;
	
	if(score_tens < 10)
	{
		score_tens++;
	}
	else
	{
		score_tens = 0;
	}
}
if(score < 10)
{
	
		LCD_Cursor(15);
		LCD_WriteData(score_tens + '0');
	
	LCD_Cursor(16);
	LCD_WriteData(score + '0');
}

if(i < arraysize)
{
	i++;
}
else{ i = 0; }
	if(m_i < matrix_tick_time)
	{
		m_i++;
	}		
	else
	{
		m_i = 0;
	 matrix_timer = Matrix_Tick(matrix_timer);
	}	 
break;

case G_correct_word:
	if(m_i < matrix_tick_time)
	{
		m_i++;
	}
	else
	{
		m_i = 0;
		matrix_timer = Matrix_Tick(matrix_timer);
	}
break;
case G_incorrect_word:
	if(m_i < matrix_tick_time)
	{
		m_i++;
	}
	else
	{
		m_i = 0;
		matrix_timer = Matrix_Tick(matrix_timer);
	}
break;
case G_correct_button:
	score++;
break;
case G_incorrect_button:
	mistake_counter++;
break;
case G_switchplayer_message:
	
	LCD_ClearScreen();
	LCD_DisplayString(1, "End of Round");
	//matrix_timer = -1;
	Matrix_Tick(-1);
			column_sel == 0x7F;
			column_val == 0x01;
	if(player == 1 && e_i == 0)
	{
		if((total_score_P1 + score) < 10)
		{
			total_score_P1 = total_score_P1 + score;
		}
		else if (!((total_score_P1 + score) < 10))
		{
			score_tens++;
			total_score_P1 = (score + total_score_P1) - 10;
		}
		
		total_score_tens_P1 = total_score_tens_P1 + score_tens;
	}
	else if(player == 2 && e_i == 0)
	{
		if((total_score_P2 + score) < 10)
		{
			total_score_P2 = total_score_P2 + score;
		}
		else
		{
			score_tens++;
			total_score_P2 =(score + total_score_P2) - 10;
			
		}
		total_score_tens_P2 = total_score_tens_P2 + score_tens;
	}
	break;
default: // ADD default behaviour below
break;
   } // State actions

}
	
	#endif