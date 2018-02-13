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
#define SLAVE_ADDRESS1  0xB0 //7 segment
#define SLAVE_ADDRESS2  0xD0 //clock modlue 
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
void writeOneByteToAddress(int registerAddress, int16 Value) {
   i2c_start();
   i2c_write(SLAVE_ADDRESS1);
   i2c_write(registerAddress);  // send the address to write
   i2c_write(Value >> 8);  //shift to high byte
   i2c_write(Value & 0xFF);  // write the value //write to low byte 
   i2c_stop();
}


// read one byte from the register address
int ReadOneBytefromAddress(int registerAddress) {
   
   int returnValue;
   
   i2c_start();
   i2c_write(SLAVE_ADDRESS2|0);
   i2c_write(registerAddress);  // send the address to read
   i2c_start();
   i2c_write(SLAVE_ADDRESS2|1);  // re-send slave addres with bit 0 = 1
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
   i2c_write(SLAVE_ADDRESS2|0);
   i2c_write(registerAddress);  // send the address to read
   i2c_start();
   i2c_write(SLAVE_ADDRESS2|1);  // re-send slave addres with bit 0 = 1
   for (i=0;i<N-1;i++) {
      delay_ms(1);                 // wait for the slave to process the data
      deviceRegister[i] = i2c_read();   // read from the slave. 
   }
   deviceRegister[i] = i2c_read(0); // the last read must use 0 as an argument
   i2c_stop();
   
}

void main() {

while(1){

   delay_ms(999);
   //writeOneByteToAddress(0,100);  // write value 100 to slave at address 0
   ReadNBytedfromAddress(0,6);
   int sec = ((deviceRegister[0]>>4)*10)+((deviceRegister[0] & 0xF));
   int min = ((deviceRegister[1]>>4)*10)+(deviceRegister[1] & 0xF);
   int hour = ((deviceRegister[2]>>4 & 0xB)*10)+(deviceRegister[2] & 0xF); //((deviceRegister[0]>>4)*10)+((deviceRegister[0] & 0xF));
   int date = deviceRegister[3]&0xF;
   char nameDay[5];
   int day=((deviceRegister[4]>>4)*10)+((deviceRegister[4] & 0xF));
   int month=((deviceRegister[5]>>4)*10)+((deviceRegister[5] & 0xF));
   //int16 year=((deviceRegister[6]>>4)*10)+((deviceRegister[6] & 0xF));
   switch(date){
   case 1:nameDay="Mon";
   break;
   case 2:nameDay="Tue";
   break;
   case 3:nameDay="Wed";
   break;
   case 4:nameDay="Thu";
   break;
   case 5:nameDay="Fri";
   break;
   case 6:nameDay="Sat";
   break;
   case 7:nameDay="Sun";
   break;
   }
   
   if(hour<10){
      if(min<10){
         if(sec<10){
            printf("0%u:0%u:0%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
            }
         else{
         printf("0%u:0%u:%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
         }
      }
      else{
         if(sec<10){
            printf("0%u:%u:0%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
            }
         else{
            printf("0%u:%u:%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
         }
   }
   }
   else{
      if(min<10){
         if(sec<10){
            printf("%u:0%u:0%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
            }
         else{
         printf("%u:0%u:%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
         }
      }
      else{
         if(sec<10){
            printf("%u:%u:0%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
            }
         else{
            printf("%u:%u:%u %s %u/%u/2018\n",hour, min, sec,nameDay,day,month);
         }
   }
   }
   writeOneByteToAddress(2,(((int16)min)*100)+sec);
   //writeOneByteToAddress(2,(((int16)hour)*100)+min);
}
}
