#include <16F886.h>
#device ADC=10 *=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

//#define RUN_BUTTON   PIN_B7



/*#INT_TIMER1
void timer1_isr() {
   set_timer1(65036); // re-set the timer1 counter to maintain a stable period
   

}*/

int counter = 0;

#INT_TIMER1
void timer1_isr(void) {
set_timer1(3036);

if(++counter >= 4){

  // output_toggle(PIN_B6);//light
   
   if (input(PIN_B6)) {  output_low(PIN_B6); }
else { output_high(PIN_B6);}
   
   counter = 0;
}

}



void main()
{
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(3036);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
      
   

   while(1) {
      
      
         
         if(!input(PIN_B7)){//switch
         
            output_toggle(PIN_B6);//light
            while(!input(PIN_B7)){
            delay_ms(1);
            }
         
         }
      
         delay_ms(1);

   }


}
