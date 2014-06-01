#ifndef __TitleScreen_h__
#define __TitleScreen_h__
unsigned char i = 1; //position of bee
unsigned char m = 0; //timer for start message
const unsigned char screen_size = 16; //total width of screen

////////////CHARACTERS FOR BEE
 const unsigned char beebutt_top[8] = {0x00, 0x00, 0x00, 0x00, 0x07, 0x0A, 0x0A, 0x12};  
 const unsigned char beeabd_top[8] = {0x00, 0x00, 0x00, 0x00, 0x1E, 0x0B, 0x0A, 0x0A}; 
const unsigned char beehead_top[8] = {0x00, 0x00, 0x02, 0x05, 0x08, 0x1E, 0x11, 0x14}; 
  
          
const unsigned char beebutt_bottom[8] = {0x12, 0x0A, 0x0A, 0x07, 0x00, 0x00, 0x00, 0x00}; 
const unsigned char beeabd_bottom[8] = {0x0A, 0x0A, 0x0B, 0x1E, 0x00, 0x00, 0x00, 0x00}; 
const unsigned char beehead_bottom[8] = {0x10, 0x11, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00}; 
              
///////////////// 


//State Machine for Start message
enum TS_States { TS_intial_state, TS_bee, TS_start_message } TS_State;

TickFct_TitleScreen() {
   switch(TS_State) { // Transitions
      case -1:
         TS_State = TS_intial_state;
         break;
         case TS_intial_state: 
         if (1) {
            TS_State = TS_start_message;
         }
         break;
		 
      case TS_bee: 
        if (i < screen_size+3) {
            TS_State = TS_bee;
         }
         else if (!(i < screen_size+3)) {
			
            TS_State = TS_intial_state;
         }
		 break;
		 
	  case TS_start_message:
		if(m < 3)
		{
			TS_State = TS_start_message;
		}						
		else
		{
			TS_State = TS_bee;
		}			
         break;
      default:
         TS_State = TS_intial_state;
		 LCD_ClearScreen();
   } // Transitions

   switch(TS_State) { // State actions
      case TS_intial_state:
         i = 1;
		 m = 0;
         break;
      case TS_bee:
	  LCD_ClearScreen();
	  ///BEE FACE
	  if(i < screen_size+1)
	  {
	  	 LCD_build(4, beehead_top);
		 LCD_Cursor(i);
		 LCD_WriteData(4);
		  	 
		 LCD_build(5, beehead_bottom);
		 LCD_Cursor(16+i);
		 LCD_WriteData(5);
	  }
	  //BEE ABDOMIN
	  if(i > 1 && i < screen_size+2)
	  {  
		LCD_build(1, beeabd_top);
		LCD_Cursor(i-1);
		LCD_WriteData(1);
		  	  
		LCD_build(3, beeabd_bottom);
		LCD_Cursor(15+i);
		LCD_WriteData(3);
	  }		
	  //BEE BUTT
	 if(i > 2 && i < screen_size+3)
	 {
	  LCD_build(0, beebutt_top);
	  LCD_Cursor(i-2);
	  LCD_WriteData(0);

	  LCD_build(2, beebutt_bottom);
	  LCD_Cursor(14+i);
	  LCD_WriteData(2);
	 }
         i++;
         break;
		 
	case TS_start_message:
		m++;
		LCD_ClearScreen();
		LCD_DisplayString(1, "Start!");
		 
      default: // ADD default behaviour below
      break;
   } // State actions

}
#endif
