/*
 * lab01.c
 *
 * Created: 10/1/2020 1:32:13 PM
 * Author: Ghazaleh Zehtab
 */

#include <io.h>
#include <delay.h>


unsigned char sevenseg[]=
    {  
        
        0b00111111,  //0   
        0b00000110,  //1
        0b01011011,  //2   
        0b01001111, //3  
        0b01100110, //4 
        0b01101101, //5
        0b01111101, //6  
        0b0000111,  //7       
        0b01111111, //8
        0b01101111 //9   
        
    } ;

//question 1 
void AllLedON_4Times(void){

    unsigned int i; //integer as counter
    DDRB=0xFF;       // define port B as output
    for(i=0;i<4;i++)
    {        
       PORTB=0xFF;      //turn on all portB
       delay_ms(500);  //delay         
       PORTB=0x00;     //turn off the portB
       delay_ms(500);       
    }
}
//question 2
void DancingLight(void){
    
    unsigned int i; //integer as counter
    unsigned int num;
    num=1;
    DDRB=0xFF;       // define port B as output
    for(i=0;i<20;i++)
    {        
       PORTB=num;      //turn on all portB  
       delay_ms(150);   
       num = num * 2;    // turn on next LED
       if (num > 128){    //if last on in ON back to the beginig
        num= 1;
       } 
    }
}
//question 3
void DiplayPortA_onLEDs(void){
    unsigned int i=0;
    DDRA=0x00;
    DDRB=0xFF;
    while(i<3000){   
        PORTB=PINA; 
        i++;
        delay_ms(1);
    }
} 
//question 4
void NineToZero(void){
    DDRC=0xFF;
    DDRD=0x0F;
    DDRD.0=1;
    DDRD.1=1;
    DDRD.2=1;
    DDRD.3=1;
    PORTC=0b01101111; //9
    delay_ms(500);
    PORTC=0b01111111;    //8
    delay_ms(500);
    PORTC=0b0000111;   //7
    delay_ms(500);
    PORTC=0b01111101;   //6
    delay_ms(500);
    PORTC=0b01101101;    //5
    delay_ms(500);
    PORTC=0b01100110;   //4
    delay_ms(500);
    PORTC=0b01001111;   //3
    delay_ms(500);
    PORTC=0b01011011;    //2
    delay_ms(500); 
    PORTC=0b00000110;    //1
    delay_ms(500);
    PORTC=0b00111111;    //0
    delay_ms(500);
    
    
} 
// question 5

void Reduce(void){
       
    unsigned int number=0; 
    unsigned int numberCopy=0; 
    unsigned int FirstDigit=0;
    unsigned int SecondDigit=0;
    unsigned int ThirdDigit=0;
    unsigned int Deci=0;        // after point
    DDRA=0x00;
    DDRC=0xFF;
    DDRD=0x00;  
    number= PINA;
    numberCopy = number  *10;   //FOR making decimal easier
    while(numberCopy>0){ 
        delay_ms(50); 
        number=numberCopy; 
        Deci=number%10;
        number= number /10;
        FirstDigit=number%10;
        number= number /10; 
        SecondDigit = number %10;  
        number= number /10;
        ThirdDigit= number; 
        DDRD.2=1;
        PORTC= sevenseg[FirstDigit]+ 0b10000000;   //point on
        delay_ms(1); 
        DDRD.2=0;
        DDRD.1=1;
        PORTC= sevenseg[SecondDigit];
        delay_ms(1); 
        DDRD.1=0;
        DDRD.0=1;
        PORTC= sevenseg[ThirdDigit]; 
        delay_ms(1); 
        DDRD.0=0;
        DDRD.3=1;
        PORTC= sevenseg[Deci];
        delay_ms(1); 
        DDRD.3=0;
        numberCopy = numberCopy - 2 ;
          
        
    }
    
    
} 

// question 6
void reset7seg(void){

    unsigned int number=0; 
    unsigned int numberCopy=0; 
    unsigned int FirstDigit=0;
    unsigned int SecondDigit=0;
    unsigned int ThirdDigit=0;
    unsigned int Deci=0;        // after point   
    unsigned int fib=0;
    unsigned int foo=0;
    DDRA=0x00;
    DDRC=0xFF;
    DDRD=0x00;  
    number= PINA;
    numberCopy = number  *10;   //FOR making decimal easier
    while(numberCopy>0){ 
      
        delay_ms(50); 
        number=numberCopy; 
        Deci=number%10;
        number= number /10;
        FirstDigit=number%10;
        number= number /10; 
        SecondDigit = number %10;  
        number= number /10;
        ThirdDigit= number; 
        DDRD.2=1;
        PORTC= sevenseg[FirstDigit];   //point off
        delay_ms(1); 
        DDRD.2=0;
        DDRD.1=1;
        PORTC= sevenseg[SecondDigit];
        delay_ms(1); 
        DDRD.1=0;
        DDRD.0=1;
        PORTC= sevenseg[ThirdDigit]; 
        delay_ms(1); 
        DDRD.0=0;
        DDRD.3=1;
        PORTC= sevenseg[Deci];
        delay_ms(1); 
        DDRD.3=0;
        numberCopy = numberCopy - 2 ;
        
         if (PIND.7==0){               //reduce that number from main number in all 4 if
             foo= numberCopy / 10;           //fib and foo are temp
             foo = foo/10;
             foo = foo/10;
             fib= foo % 10;
             fib = fib *1000;
             numberCopy= numberCopy - fib;
             SecondDigit= 0 ;
             ThirdDigit= 0;
            
            //delay_ms(1000);
        }
        if (PIND.6==0){  
             foo= numberCopy / 10; 
             foo = foo/10;
             fib= foo % 10;
             fib = fib *100;
             numberCopy= numberCopy - fib;
             SecondDigit= 0 ;
        }
        if (PIND.5==0){ 
             foo= numberCopy / 10;
             fib= foo % 10;
             fib = fib *10;
             numberCopy= numberCopy - fib;
             FirstDigit= 0;
        }
        if (PIND.4==0){ 
             //delay_ms(1000); 
             fib= numberCopy % 10;
             numberCopy= numberCopy - fib;
             Deci= 0;
            
        }
             
    }
    
    
}

void main(void)
{
    // Please write your application code here  
    AllLedON_4Times();   // call function of question 1    
    DancingLight(); //call function for question 2 
    NineToZero();      //call function for question 4
    while(1){     
        DiplayPortA_onLEDs(); //  call function for question 3
        Reduce();   //call function for question 5 
        reset7seg(); //call function for question 6   
    }   
    
    
    
}