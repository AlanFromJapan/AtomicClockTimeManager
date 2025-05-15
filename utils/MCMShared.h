
#ifndef __MCMShared_h__
#define __MCMShared_h__

// --------- Constants taken from Arduino.h ----------
#define HIGH 0x1
#define LOW  0x0

#define true 0x1
#define false 0x0

#define LSBFIRST 0
#define MSBFIRST 1
// --------- /Constants taken from Arduino.h ----------



// Convert normal decimal numbers to binary coded decimal
unsigned char decToBcd(unsigned char val)
{
  return ( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
unsigned char bcdToDec(unsigned char val)
{
  return ( (val/16*10) + (val%16) );
}

//alternate way to do it
unsigned char bcd2Dec (unsigned char val){
  unsigned char v  = val & 0x0f;
  
  if ((val  & (1 << 4)) != 0){
    v += 10;
  }
  if ((val  & (1 << 5)) != 0){
    v += 20;
  }
  if ((val  & (1 << 6)) != 0){
    v += 40;
  }
  
  return v;
}
#endif //__MCMShared_h__
