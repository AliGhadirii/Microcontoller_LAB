#include <headers.h>
unsigned char MyKeypad(void){
    DDRB=0xF0;
    PORTB=0xFF;
        do{
            PORTB &= 0x0F; //ground all rows at once
            colloc = (PINB & 0x0F) ;//read the columns
        } while(colloc != 0x0F);//check until all keys released
        
        do
        {
            do
            {
                delay_ms(20);
                colloc = (PINB & 0x0F);//check if any key is pressed
            }while(colloc == 0x0F);
            delay_ms(20);
            colloc = (PINB & 0x0F);    
        }while(colloc == 0x0F);
        
        while(1){
            PORTB=0xEF;//ground row 0
            colloc = (PINB & 0x0F);//read all columns
            if(colloc != 0x0F){ //we konw column here
                rowloc=0;
                break;
            }  
            
            PORTB=0xDF;//ground row 1
            colloc = (PINB & 0x0F);//read all columns
            if(colloc != 0x0F){ //we konw column here
                rowloc=1;
                break;
            }
            
            PORTB=0xBF;//ground row 2
            colloc = (PINB & 0x0F);//read all columns
            if(colloc != 0x0F){ //we konw column here
                rowloc=2;
                break;
            }
            
            PORTB=0x7F;//ground row 3
            colloc = (PINB & 0x0F);//read all columns
            if(colloc != 0x0F){ //we konw column here
                rowloc=3;
                break;
            }  
        }
        
        //check column and send result to LCD
        
        if (colloc == 0x0E){
            lcd_putchar(data_key [rowloc][0] );
            return (data_key [rowloc][0]);
            } 
        else if (colloc == 0x0D){
            lcd_putchar(data_key [rowloc][1] );
            return(data_key [rowloc][1] ); 
            }
        else if (colloc == 0x0B){
            lcd_putchar(data_key [rowloc][2] );
            return (data_key [rowloc][2]);
            }
        else { 
            lcd_putchar(data_key [rowloc][3] );
            return (data_key [rowloc][3]);
            }
}