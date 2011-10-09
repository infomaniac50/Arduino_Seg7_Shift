/*
  Seg7.h - A library to control the TPIC6B595 Serial to Parallel Shift Register
  Created by Derek Chafin, October 8, 2011
  Released into the public domain.
*/

#include "Seg7.h"
#include "WProgram.h"
#define GATE_DELAY 20

Seg7::Seg7(int dataPin, int clockPin, int latchPin, int clearPin)
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  _latchPin = latchPin;
  _clearPin = clearPin;
}

void Seg7::init(byte* bin1)
{
  digits = 1;
  _bin1 = bin1;
}

void Seg7::init(byte* bin1, byte* bin2)
{
  digits = 2;
  _bin1 = bin1;
  _bin2 = bin2;
}

void Seg7::init(byte* bin1, byte* bin2, byte* bin3)
{
  digits = 3;
  _bin1 = bin1;
  _bin2 = bin2;
  _bin3 = bin3;
}

void Seg7::init(byte* bin1, byte* bin2, byte* bin3, byte* bin4)
{
  digits = 4;
  _bin1 = bin1;
  _bin2 = bin2;
  _bin3 = bin3;
  _bin4 = bin4;
}

void Seg7::sendNumber(int number)
{
  clear();

  switch(digits)
  {
    case 4:
      shiftOut(_dataPin, _clockPin, LSBFIRST, _bin4[getDigit(number, 3)]);
    case 3:
      shiftOut(_dataPin, _clockPin, LSBFIRST, _bin3[getDigit(number, 2)]);
    case 2:
      shiftOut(_dataPin, _clockPin, LSBFIRST, _bin2[getDigit(number, 1)]);
    case 1:
      shiftOut(_dataPin, _clockPin, LSBFIRST, _bin1[getDigit(number, 0)]);
  }
  
  pulsePin(_latchPin, HIGH);  
}

void Seg7::clear()
{
  pulsePin(_clearPin, LOW);
  pulsePin(_latchPin, HIGH);
}

int Seg7::getDigit(int number, int pos)
{
  return (number / (int)pow(10, pos)) % 10;
}

void Seg7::pulsePin(int pin, int active)
{
  if (active == HIGH)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(GATE_DELAY);
    digitalWrite(pin, LOW);
  }
  else
  {
    digitalWrite(pin, LOW);
    delayMicroseconds(GATE_DELAY);
    digitalWrite(pin, HIGH);
  }
}
