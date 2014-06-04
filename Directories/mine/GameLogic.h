#ifndef __Gamer_h__
#define __Gamer_h__

#include <io.h>
#include "mine/Matrix.h"
//EASY - 5th grade level words taken from http://www.k12reader.com/fifth-grade-spelling-words/
const unsigned char *correct_easy[] = {"usually", "even", "understood", "blank", "five", "Sunday", "dancer", "curves", "noisy", "ten", "December", "brilliant", "adapt", "decadent", "fifteen", "glucose", "least", "ears", "uniform", "twenty", "deception", "voice", "problem", "firm", "number", "university", "cover", "poison", "picture", "thirty" };
//http://www.sightwordsgame.com/spelling/misspelled-words-grade/
const unsigned char *incorrect_easy[] = {"thier", "galaxi", "woory", "erorr", "aquire", "amature", "colum", "mideval", "miniture", "cerimony", "surpise", "califlower", "cheezburger", "accross", "addrress", "manuver", "recieve", "athelete", "probly", "vacuume", "idealy", "existance", "begginer", "markit", "oxigen", "wokring", "libary", "junp", "peice" };
	//HARD - words taken from http://grammar.yourdictionary.com/spelling-and-word-lists/misspelled.html, http://www.oxforddictionaries.com/us/words/common-misspellings, 
const unsigned char *correct_hard[] = {"futuristic", "mischievous", "cytoplasm", "acquit", "conscious", "daiquiri", "foreign", "inoculate", "liaison", "precede", "publicly", "sergeant", "supersede", "tyranny", "disastrous", "sacrilegious", "siege", "propaganda", "deductible", "embarrass", "existence", "consensus", "inadvertent", "indispensable", "perseverance", "prerogative", "judgment", "lightning", "repetition", "potatoes" };
	const unsigned char *incorrect_hard[] = {"ignorence", "occurence", "precedessor", "athiest", "bellweather", "commited", "dicsipline", "exilerate", "playwrite", "mispell", "occasionaly", "restarant", "Febary", "Farenheit", "pharoah", "threshhold", "glamourous", "chauffer", "assasination", "alchohol", "kernal", "vegatarian", "secratary", "prophesy", "parliment", "religous", "underate", "repitition", "jewelery", "flourescent" };
//"Random" output array decides which what position in the above arrays to choose. between 1 - 29, 50 total numbers
const unsigned char *word_pattern[] = {11, 27, 10, 14, 9, 12, 1, 16, 23, 22, 10, 26, 6, 11, 21, 15, 22, 17, 2, 14, 19, 27, 22, 18, 11, 10, 24, 7, 15, 12, 18, 23, 26, 5, 19, 8, 19, 20, 20, 16, 27, 12, 11, 7, 9, 25, 7, 5, 10, 25};
	//88 total, used for correct/incorrect array choices
const unsigned char *word_correct_pattern[] = {0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,0,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,1,0,0};

const unsigned char arraysize = 30; // the amount of words in in/correct array
const unsigned char amount_rounds =  1; // 3 rounds for each player
const unsigned char wait_two_seconds = 20; //Timer is currenty 100ms. 100*20 =  2000ms == 2sec
const unsigned char matrix_tick_time = 3; // Timer for speed of timer for a player. 100ms * 3 = 300ms per dot on matrix 
unsigned char return_value = 1;

//////////////////////////////////////////////////////////////////////////
unsigned char turn = 0; //counter for the amount of turns take
unsigned char player = 1; //determines whose turn it is
unsigned char p_i = 0; //player iterator for time
unsigned char e_i = 0; //end of round iterator for time
unsigned char m_i = 0; //Matrix iterator to slow it down
unsigned char g_i = 0; //end of game message iterator

unsigned char word_correctness = 0;  //determines is a correctly spelled word shall appear
unsigned char word_choice = 0; //chooses a word from an array
unsigned char wc_i = 0; //iterators for word choice function
unsigned char wc_j = 0;
unsigned char score = 0; //keeps score for that round
unsigned char score_tens = 0; //if it goes over 9
unsigned char mistake_counter = 0; //counts # of mistakes - every 3 mistakes you lose round early
unsigned char total_score_P1 = 0; //Total score for Player 1
unsigned char total_score_tens_P1 = 0; //Total score for Player 1
unsigned char total_score_P2 = 0; //Total Score for Player 2
unsigned char total_score_tens_P2 = 0; //Total Score
int matrix_timer = 0; //matrix position indicator

unsigned char difficulty = 0; //Player Difficulty

//	unsigned char random_number = 0;
	
enum G_States { G_GAME_START, G_difficulty, G_switchplayer, G_pickwordchoice, G_output, G_correct_word, G_incorrect_word, G_correct_button, G_incorrect_button, G_switchplayer_message, G_end_game} G_State;

int TickFct_GAME() {
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
		G_State = G_difficulty;
	}
	break;
	
	case G_difficulty:      //SELECT DIFFICULTY
	if(button_P2_correct) //EASY
	{
		difficulty = 0;
		G_State = G_switchplayer;
	}
	else if(button_P1_correct) //HARD
	{
		difficulty = 1;
		G_State = G_switchplayer;
	}
	else if(!button_P1_correct && !button_P1_incorrect)
	{
		G_State = G_difficulty;
	}
	
	break;
	case G_switchplayer: //Switches between the two players
	if(turn > amount_rounds)
	{
		G_State = G_end_game;
	}
	else if(p_i < wait_two_seconds)  //STAY HERE UNTIL 2 SECOND PASSES
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
		if(stop_timer)
		{
			G_State = G_switchplayer_message;
		}
		else{
	G_State = G_output;}
	break;
	
	case G_output: //Output Word and Score to Screen 
		if(stop_timer)
		{
			G_State = G_switchplayer_message;
		}
	if (word_correctness) {
		G_State = G_correct_word;
	}
	else if(!word_correctness){
		G_State = G_incorrect_word;
	}
	break;
	
	case G_correct_word: //Wait for button response
	if(stop_timer)
	{
		G_State = G_switchplayer_message;
	}
	if(player == 1)
	{
		if (!button_P1_correct && !button_P1_incorrect) {   //if no buttons pressed, do nothing
			if(stop_timer)
			{
				G_State = G_switchplayer_message;
			}			
			else{
			G_State = G_correct_word;}
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
		if (!button_P2_correct && !button_P2_incorrect) 
		{   //if no buttons pressed, do nothing
			if(stop_timer)
			{			
				G_State = G_switchplayer_message;}
		    else{
			G_State = G_correct_word;}
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
		if(stop_timer)
		{
			G_State = G_switchplayer_message;
		}
	if(player == 1)
	{
		if(!button_P1_correct && !button_P1_incorrect) //incorrect word and correct button pressed
		{
			if(stop_timer)
			{
				G_State = G_switchplayer_message;
			}
			else{
			G_State = G_incorrect_word;}
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
				if(stop_timer)
				{
					G_State = G_switchplayer_message;
				}
				else{
				G_State = G_incorrect_word;}
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
		if(stop_timer)
		{
			G_State = G_switchplayer_message;
		}
	else
	{
		G_State = G_pickwordchoice;
	}	
	break;
	
	case G_incorrect_button: //Count # of mistakes. if too many, switch player
		if(stop_timer)
		{
			G_State = G_switchplayer_message;
		}
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
	if(turn > (amount_rounds - 1))
	{
		G_State = G_end_game;
	}
	else if(!(e_i < wait_two_seconds)) //swap players and send to player screen
	{
		if(player == 1)
		{
			player = 2;
			turn++;
		}
		else if(player == 2)
		{
			player = 1;
			turn++;
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
	
	case G_end_game:
	if(g_i < wait_two_seconds)  //STAY HERE UNTIL 2 SECOND PASSES
	{
		G_State = G_end_game;
	}
	else{
		return_value = 0;
		return 0;
	}
	break;
	
	default:
	G_State = G_GAME_START;
	
} // Transitions





switch(G_State) { // State actions
case G_GAME_START:
break;

case G_difficulty:
	if(1)
	{
		LCD_ClearScreen();
		LCD_DisplayString(1, "Easy or Hard?");
	}
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

case G_output:
LCD_ClearScreen();

word_choice = word_pattern[i];     //"Randomly" generated words array
if(word_correctness && difficulty == 0)
{
	LCD_DisplayString(1, correct_easy[word_choice]); //Displays word CORRECT EASY
}
else if(!word_correctness && difficulty == 0)
{
	LCD_DisplayString(1, incorrect_easy[word_choice]); //Displays word INCORRECT EASY
}

else if(word_correctness && difficulty == 1)
{
	LCD_DisplayString(1, correct_hard[word_choice]); //Displays word CORRECT HARD
}
else if(!word_correctness && difficulty == 1)
{
	LCD_DisplayString(1, incorrect_hard[word_choice]); //Displays word EASY
}


//SCORE OUTPUT MIDGAME
if(!(score < 10)) //OUPTPUT VALUES GREATER THAN 9
{
	score = score - 10;  //can only display one digit at a time. 
	
	if(score_tens < 10)  
	{
		score_tens++;
	}
	else
	{
		score_tens = 0;
	}
}

	LCD_Cursor(15);             //displaying total score
	LCD_WriteData(score_tens + '0');
	
	LCD_Cursor(16);
	LCD_WriteData(score + '0');

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
	if(turn < amount_rounds)
	{
		LCD_DisplayString(1, "End of Round");
	}	

	Matrix_Tick(-1);   ///RESET MATRIX TIMER
			column_sel == 0x7F;
			column_val == 0x01;
	if(player == 1 && e_i == 0)  //UPDATING SCORES
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
	
	case G_end_game:
	if(1)
	{
		g_i++;
		LCD_ClearScreen();
		LCD_DisplayString(1, "End of Game");
	}	
	
	break;
default: // ADD default behaviour below
break;
   } // State actions

}
	
	#endif