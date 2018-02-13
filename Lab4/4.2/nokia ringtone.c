#include <16F886.h>
#device ADC=10 *=16

#FUSES NOWDT //No Watch Dog Timer
#FUSES PUT //Power Up Timer
#FUSES NOMCLR //Master Clear pin not enabled
#FUSES NOPROTECT //Code not protected from reading
#FUSES NOCPD //No EE protection
#FUSES BROWNOUT //Brownout reset
#FUSES IESO //Internal External Switch Over mode enabled
#FUSES FCMEN //Fail-safe clock monitor enabled
#FUSES NOLVP //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG //No Debug mode for ICD
#FUSES NOWRT //Program memory not write protected
#FUSES BORV40 //Brodddddwnout reset at 4.0V
#FUSES RESERVED //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#use i2c(MASTER, I2C1, FORCE_HW) // configure the i2c port
#define SLAVE_ADDRESS  0xB0



int16 C = 65298,CSH = 65311,D = 65324,EB = 65336,E = 65347,F = 65358,FSH = 65199,G = 65377,GSH = 65236,A = 65394,Bb = 65402,B = 65283,DT = 65111,ET = 65157,AT = 65252,CSHT = 65086;
int16 note[13];



int count_note = 1 ;

#INT_TIMER1
void timer1_isr() {

set_timer1(note[count_note]); // ?????????????? ISR ???? ?????????????????????

//if (input(PIN_B5)) {  output_low(PIN_B5); }
//else { output_high(PIN_B5);}
output_toggle(PIN_B4);
}


void main() {

   note[1] = E;
note[2] = D;
note[3] = FSH;
note[4] = GSH;
note[5] = CSH;
note[6] = B;
note[7] = DT;
note[8] = ET;
note[9] = B;
note[10] = AT;
note[11] = CSH;
note[12] = E;
note[13] = A;


   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(note[1]); 
   delay_ms(500);
   count_note++;
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   
   while (1) {
   
      set_timer1(note[count_note]);
      delay_ms(200);
      
      if(count_note==4|count_note==8|count_note==11|count_note == 12|count_note==13) {
      delay_ms(500);
      }
      if(count_note==13)count_note=1;
      count_note++;
   }
   
   
}
