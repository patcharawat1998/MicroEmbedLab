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



int16 C = 65298,CSH = 65311,D = 65324,EB = 65336,E = 65347,F = 65358,FSH = 65368,G = 65377,GSH = 65386,A = 65394,Bb = 65402,B = 65410;
int16 note[44];



int count_note = 1 ;

#INT_TIMER1
void timer1_isr() {

set_timer1(note[count_note]); // ?????????????? ISR ???? ?????????????????????

//if (input(PIN_B5)) {  output_low(PIN_B5); }
//else { output_high(PIN_B5);}
output_toggle(PIN_B4);
}


void main() {

   note[1] = C;
note[2] = C;
note[3] = G;
note[4] = G;
note[5] = A;
note[6] = A;
note[7] = G;
note[8] = F;
note[9] = F;
note[10] = E;
note[11] = E;
note[12] = D;
note[13] = D;
note[14] = D;
note[15] = D;
note[16] = C;
note[17] = G;
note[18] = G;
note[19] = F;
note[20] = E;
note[21] = E;
note[22] = D;
note[23] = G;
note[24] = G;
note[25] = G;
note[26] = F;
note[27] = E;
note[28] = E;
note[29] = D;
note[30] = C;
note[31] = C;
note[32] = G;
note[33] = G;
note[34] = A;
note[35] = A;
note[36] = G;
note[37] = F;
note[38] = F;
note[39] = E;
note[40] = E;
note[41] = D;
note[42] = D;
note[43] = C;

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   //set_timer1(note[1]); 
   //delay_ms(750);
   //count_note++;
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   
   while (1) {
   
      set_timer1(note[count_note]);
      
      if(count_note==12|count_note==13|count_note==14|count_note==15|count_note==23|count_note==24|count_note==25){
      delay_ms(250);
      }
      else{
      delay_ms(500);
      }
      
      if(count_note==7|count_note==16|count_note==19|count_note==22|count_note==26|count_note==29|count_note==36){
      delay_ms(500);
      }
      count_note++;
      if(count_note == 43) {
      
      delay_ms(1000);
      count_note = 1;
      }
   }
   
   
}
