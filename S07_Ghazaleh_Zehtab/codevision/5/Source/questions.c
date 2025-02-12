#include <headers.h>

//question1
// 0 = OFF , 1= enable_noneinterrupt , 2= enable_interrupt
void init_uart(unsigned int my_tx,unsigned int my_rx,long int my_baudrate){
    float UBBR_Set=0;
    int int_UBBR_Set=0;
    UBBR_Set = ((8 * 1000000) / (16 * my_baudrate))-1; 
    int_UBBR_Set = (int)UBBR_Set; 
 
    if (my_tx == 0 && my_rx == 0){ 
 
        // USART disabled 
    } 
    else if (my_rx == 1 && my_tx == 1){ 
        UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM); 
        UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8); 
        UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL); 
        if (int_UBBR_Set < 0xFF){ 
                UBRRL = int_UBBR_Set; 
        } 
        else { 
                UBRRL = int_UBBR_Set % 0xFF; 
                UBRRH = int_UBBR_Set / 0xFF; 
        } 
    } 
    else if (my_tx == 1 && my_rx == 2 ){ 
        UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM); 
        UCSRB=(1<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8); 
        UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL); 
        if (int_UBBR_Set < 0xFF){ 
                UBRRL = int_UBBR_Set; 
        } 
        else { 
                UBRRL = int_UBBR_Set % 0xFF; 
                UBRRH = int_UBBR_Set / 0xFF; 
        } 
            #asm("sei") 
    } 
    else if (my_rx == 2 && my_tx == 2){ 
        UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM); 
        UCSRB=(1<<RXCIE) | (1<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8); 
        UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL); 
         if (int_UBBR_Set < 0xFF){ 
                UBRRL = int_UBBR_Set; 
        } 
        else { 
                UBRRL = int_UBBR_Set % 0xFF; 
                UBRRH = int_UBBR_Set / 0xFF; 
        } 
            #asm("sei") 
    } 
    else {
        //disable 
       } 
}
//**************************************************************
void question2(unsigned int mtx,unsigned int mrx,long int mbaud){
    unsigned char name[55]="";
    unsigned char in='';  
    int i=0;  
    init_uart(mtx,mrx,mbaud);
    puts("part 2 is running!\r");
    in = getchar();
    putchar(in); 
    name[0]='(';
    i++;
    while (in!='\r'){ 
        name[i]=in; 
        in = getchar();
        putchar(in);
        i++;    
    }
    name[i]=')';  
    puts(name);    
}
//********************************************
void question3(unsigned int mtx,unsigned int mrx,long int mbaud){
    unsigned char in3='';
    //unsigned char temp='';
    int a=0;
    unsigned char str[3]="";
    init_uart(mtx,mrx,mbaud);
    puts("part 3 is running!\r");
    //temp = getchar_nv();
    in3 = getchar_nv(); 
    switch (in3){
        case '0':
            a=0;
            break;
        case '1':
            a=1;
            break;
        case '2':
            a=2;
            break;
        case '3':
            a=3;
            break;
        case '4':
            a=4;
            break;
        case '5':
            a=5;
            break;
        case '6':
            a=6;
            break;
        case '7':
            a=7;
            break; 
        case '8':
            a=8;
            break;
        case '9':
            a=9;
            break;
        default:
            a=100;
    }  
    if( a>=0 && a<10){
        puts("\rTx:");
        putchar(in3);
        puts("\rRx: Data is a integer and 10*data=");
        a=a*10;
        sprintf(str, "%d", a);
        puts(str);
        puts("\r");
     } 
    
    else if(in3=='D'){
        lcd_puts("LCD delete");
    } 
    
    else if(in3=='H'){
        puts("\rMicro Lab in Pandemic\r");
    }
    
    else {
        puts("\rNo function defined!\r");
    }    

}

void question4(unsigned int mtx,unsigned int mrx,long int mbaud){
    unsigned char my_data[55]="";
    unsigned char in4='';  
    int i=0;
    int a=0;
    int j=0;  
    init_uart(mtx,mrx,mbaud);
    puts("part 4 is running!\r");
    in4 = getchar_nv();
    putchar(in4); 
    while (in4!='\r'){ 
        my_data[i]=in4; 
        in4 = getchar_nv();
        putchar(in4);
        i++;    
    }  
    for (j=1;my_data[j]!=')';j++){ 
        switch (my_data[j]){
        case '0':
            a=0;
            break;
        case '1':
            a=1;
            break;
        case '2':
            a=2;
            break;
        case '3':
            a=3;
            break;
        case '4':
            a=4;
            break;
        case '5':
            a=5;
            break;
        case '6':
            a=6;
            break;
        case '7':
            a=7;
            break; 
        case '8':
            a=8;
            break;
        case '9':
            a=9;
            break;
        default:
            a=100;
    }     
    }
    if (a>9){
       puts("\rFrame must be 5 integer\r"); 
    }
    else if(i!=7){  
        puts("\rLength of frame not correct\r");
    }
    else { 
        puts("\tFrame is correct\r");
        lcd_puts(my_data);
    }  
}
