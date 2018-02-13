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
void main() {
    setup_adc_ports(sAN0); // setup PIN A0 as analog input 
    setup_adc( ADC_CLOCK_INTERNAL ); 

    printf("Sampling:\r\n");
    set_adc_channel( 0 ); // set the ADC chaneel to read 
    delay_us(100); // wait for the sensor reading to finish
    int16 i=250,j=90;
    while (1) {
       printf("Sensor value = %Lu\r\n", read_adc()); 
       //delay_ms(500); 
       printf("$%lu %lu %lu;",read_adc(),i,j);
         delay_ms(5);
       

      //bad case
       /*
         if(read_adc()>210){
       output_low(PIN_B6);
         }
       if(read_adc()<210){
       output_high(PIN_B6);
       }
       */ 
       
         delay_ms(100);
         if(read_adc()>250){
       output_low(PIN_B6);
         }
       if(read_adc()<90){
       output_high(PIN_B6);
       }
    }
}
