/*
  Seg7.h - A library to control the TPIC6B595 Serial to Parallel Shift Register
  Created by Derek Chafin, October 8, 2011
  Released into the public domain.
*/

#ifndef Seg7_h
#define Seg7_h

#include "WProgram.h"
class Seg7
{
  public:
    Seg7(int dataPin,int clockPin, int latchPin, int clearPin);
    void init(byte* bin1);
    void init(byte* bin1, byte* bin2);
    void init(byte* bin1, byte* bin2, byte* bin3);
    void init(byte* bin1, byte* bin2, byte* bin3, byte* bin4);
    void sendNumber(int number);
    void clear();
  private:
    int _dataPin;
    int _clockPin;
    int _latchPin;
    int _clearPin;
    byte *_bin1;
    byte *_bin2;
    byte *_bin3;
    byte *_bin4;
    int digits; 
    int getDigit(int number, int pos);
    void sendByte(byte data);
    void pulsePin(int pin, int active);    
};
#endif
