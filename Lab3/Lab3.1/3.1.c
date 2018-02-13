#include <16F886.h>
#device adc=10

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

///////////////////////////////////////////////////////////////////////////
// Project constants
///////////////////////////////////////////////////////////////////////////
#define SLAVE_ADDRESS  0xB0
#define REGISTER_SIZE  8       // the slave's register size. Resize to
                                // fit your needs


// Config the serial port hardware on the PIC
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

// setup the I2C port
#use i2c(MASTER, I2C1, FORCE_HW)

///////////////////////////////////////////////////////////////////////////
// This is the main device register
///////////////////////////////////////////////////////////////////////////
int deviceRegister[REGISTER_SIZE]={0}; // device register


// Write one byte to the register address
void writeOneByteToAddress(int registerAddress, int Value) {
   i2c_start();
   i2c_write(SLAVE_ADDRESS|0);
   i2c_write(registerAddress);  // send the address to write
   i2c_write(Value);  // write the value
   i2c_stop();
}


// read one byte from the register address
int ReadOneBytefromAddress(int registerAddress) {
   
   int returnValue;
   
   i2c_start();
   i2c_write(SLAVE_ADDRESS|0);
   i2c_write(registerAddress);  // send the address to read
   i2c_start();
   i2c_write(SLAVE_ADDRESS|1);  // re-send slave addres with bit 0 = 1
   delay_ms(1);                 // wait for the slave to process the data
   returnValue = i2c_read(0);   // read from the slave. 
   i2c_stop();
   
   return(returnValue);
}

// read N byte from the register address and store in the global array deviceRegister
// Note. the size of deviceRegister[] must be >= registerAddress + N
void ReadNBytedfromAddress(int registerAddress, int N) {
   
   int i;
   
   i2c_start();
   i2c_write(SLAVE_ADDRESS|0);
   i2c_write(registerAddress);  // send the address to read
   i2c_start();
   i2c_write(SLAVE_ADDRESS|1);  // re-send slave addres with bit 0 = 1
   for (i=0;i<N-1;i++) {
      delay_ms(1);                 // wait for the slave to process the data
      deviceRegister[i] = i2c_read();   // read from the slave. 
   }
   deviceRegister[i] = i2c_read(0); // the last read must use 0 as an argument
   i2c_stop();
   
}

void main() {
   delay_ms(2000);
   writeOneByteToAddress(3,1);  // write value 100 to slave at address 2
   printf("%d",ReadOneBytefromAddress(3));
}
