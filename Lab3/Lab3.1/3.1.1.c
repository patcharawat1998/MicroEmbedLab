
#include <16F886.h>

#device ADC=10 *=16
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External SWITCH Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used FOR I/O
#FUSES NODEBUG                  //No Debug mode FOR ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 
#use delay(clock=8M)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#define RUN_BUTTON   PIN_B7
#define SLAVE_ADDRESS  0xB0
#use i2c(MASTER, I2C1, FORCE_HW) // configure the i2c port
void main()
{
int16 i;
delay_ms(1000);
for (i=9980;i<10000;i++) {
delay_ms(500);
 i2c_start();
 i2c_write(SLAVE_ADDRESS);
 i2c_write(2);//register address
 i2c_write(i >> 8);//high bit
 i2c_write(i & 0xFF);//low bit
 i2c_stop();
}
}
