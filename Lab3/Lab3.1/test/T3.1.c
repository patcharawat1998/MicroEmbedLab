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
void main() {
//!   i2c_start(); //important
//!   i2c_write(SLAVE_ADDRESS);
//!   i2c_write(2);  // set register pointer to location 2
//!   i2c_write(0x00); // send high byte
//!   i2c_write(0x0F); // send low byte
//!   i2c_stop(); //important
//------------------------------------------------

//!      for (int i=0;i<10;i++) {
//!       delay_ms(500);
//!       i2c_start();
//!       i2c_write(SLAVE_ADDRESS);
//!       i2c_write(2);
//!       i2c_write(0);
//!       i2c_write(i);
//!       i2c_stop();
//!       
//!      }

      for (int16 i=1;i<=9998;i++) {
       //delay_ms(1);
//!       i2c_start();
//!       i2c_write(SLAVE_ADDRESS);
//!       i2c_write(2);
//!       I2c_write(i >> 8);  // upper byte of 1000
//!       I2c_write(i & 0xFF); // lower byte of 1000

          i2c_start();
          i2c_write(SLAVE_ADDRESS);
          i2c_write(2);
          i2c_write(i >> 8);
          i2c_write(i & 0xFF);
          i2c_stop();
         if(i==9998){
          delay_ms(1000);
          i2c_start();
          i2c_write(SLAVE_ADDRESS);
          i2c_write(2);
          I2c_write(0x27);  // upper byte of 1000
          I2c_write(0x0F); // lower byte of 1000
          i2c_stop();
          
       
     
      }
      
    
}
}

