#include <headers.h>

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// question1_ timer
    if(PINB.5==0){ //stop
        TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
        flag=2;       
    }
    
    if(PINB.4==0){ //start
        lcd_gotoxy(0,0);
        lcd_puts(blank);
        lcd_gotoxy(0,0); 
        Timer_Init();
        flag=1;
    }
    
    if (PINB.5 == 0 && flag != 1){ //STOP is ON
        lcd_gotoxy(0,0);
        lcd_puts(blank);
        lcd_gotoxy(0,0);
        lcd_puts("00:00:00:00");
        lcd_gotoxy(0,0);
        lcd_puts(blank);
        lcd_gotoxy(0,0);
        lcd_puts("00:00:00:00");
        flag = 1;
        ms=0;
        sec=0;
        min=0;
        hour=0;
    }

}

// External Interrupt 1 service routine
//question2
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here //q2
    if(PINB.3==0){ //out
       if (Empty == 1000){ 
           //full; 
           lcd_gotoxy(0,1);
           lcd_puts(blank);
           lcd_gotoxy(0,1);
           lcd_puts("CE:1000"); 
       }
       else{
        Empty++;
        sprintf(em,"%d",Empty);
        lcd_gotoxy(0,1);
        lcd_puts(blank);
        lcd_gotoxy(0,1);
        lcd_puts(em);
        delay_ms(200);
       //lcd_puts("PIN3"); 
       }
    }
    
    else if(PINB.2==0){ //IN 
        Empty--; 
        if (Empty==0){
            lcd_gotoxy(0,1);
            lcd_puts(blank);
            lcd_gotoxy(0,1);
            lcd_puts("CE:FULL");
            delay_ms(200);
        }
        else{
            sprintf(em,"%d",Empty);
            lcd_gotoxy(0,1);
            lcd_puts(blank);
            lcd_gotoxy(0,1);
            lcd_puts(em);
            delay_ms(200);
        //lcd_puts("PIN2"); 
        }
    }

}

// Timer 0 overflow interrupt service routine
//question 1 control my timer
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    // Reinitialize Timer 0 value
    TCNT0=0xB2;
    // Place your code here

    if(ms == 99){  
        sec++;
        ms=0;
    }
    
    if (sec==59){ 
        min++;
        sec=0;
    }
    
    if(min == 59){
        hour++;
        min=0;
    } 
 
    if (hour== 24) {
        ms=0;
        sec=0;
        min=0;
        hour=0;        
    }
    ms++;
    
     sprintf(hour_char,"%d",hour);
     sprintf(min_char,"%d",min);
     sprintf(sec_char,"%d",sec);
     sprintf(ms_char,"%d",ms);

     lcd_gotoxy(0,0);
     lcd_puts(blank);
     lcd_gotoxy(0,0);
     lcd_puts(hour_char);
     lcd_puts(":");
     lcd_puts(min_char);
     lcd_puts(":");
     lcd_puts(sec_char);
     lcd_puts(":");
     lcd_puts(ms_char);
}