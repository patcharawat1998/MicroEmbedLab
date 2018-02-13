#include <16F886.h>
#device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
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

#use delay(clock=8M)

// Config the serial port hardware on the PIC
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

int1 counter=0;
int1 isHigh=0;  // a flag to check the status of the output pulse pin

#INT_TIMER1
void timer1_isr() {
   set_timer1(-64346); // re-set the timer1 counter to maintain a stable period
  counter=!counter;

}


void main()
{
   ////////////////////////////////////////////////////////////////
   // set timer1
   //
   // interrupt period = (1/20)*4*8*(65536-3036) us = 100.0 ms
   ////////////////////////////////////////////////////////////////
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(-64346); 
   enable_interrupts(INT_RB7);
   enable_interrupts(GLOBAL);
      
   int i=0;

   while(1) {
      
      if (counter) {
         output_high(PIN_B5);
      delay_ms(1000);
      output_low(PIN_B5);
      counter=!counter;

      }


   }


}
