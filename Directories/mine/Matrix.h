#ifndef __Matrix_h__
#define __Matrix_h__

unsigned char stop_timer = 0;
static unsigned char column_val = 0x01; // sets the pattern displayed on columns
static unsigned char column_sel = 0x7F; // grounds column to display pattern

enum M_Timer {m_display, m_reset};   
int Matrix_Tick(int state) {     
    // === Local Variables ===   
    static unsigned char column_val = 0x01; // sets the pattern displayed on columns   
    static unsigned char column_sel = 0x7F; // grounds column to display pattern   
    // === Transitions ===   
    switch (state) {   
		case m_reset:
		if(1)
		{
			state = m_display;
		} 
		break;
        case m_display:
		if(state == -1)
		{
			state = m_reset;
		}
		break;   
        default:            state = m_reset;   
        break;   
    }   
          
    // === Actions ===   
    switch (state) { 
		case m_reset:
		column_sel = 0x7F; 
		column_val = 0x01;
		stop_timer = 0;
		break;  

        case m_display:   // If illuminated LED in bottom right corner   

        if (column_sel == 0xFE && column_val == 0x80) {   
            stop_timer = 1;
			//column_sel = 0x7F; // display far left column   
            //column_val = 0x01; // pattern illuminates top row   
		}          
        // else if far right column was last to display (grounded)   
        else if (column_sel == 0xFE) {   
            column_sel = 0x7F; // resets display column to far left column   
            column_val = column_val << 1; // shift down illuminated LED one row   
        }   
        // else Shift displayed column one to the right   
        else {   
            column_sel = (column_sel >> 1) | 0x80;   
        }   
              
        break;   
        default:            break;   
    }   
          
    PORTC = column_val; // PORTA displays column pattern   
    PORTB = column_sel; // PORTB selects column to display pattern   
      
    return state;   
}; 

#endif