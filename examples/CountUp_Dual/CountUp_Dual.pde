/*
CountUp_Dual
Derek Chafin
October 8, 2011
Public Domain
Counts from 0 to 99 using a dual common positive 7 segment display


L = Led Segment
D = Drain Number; The number of the drain not the actual pin number

My Led Segments
A = Top
B = Top Right
C = Bottom Right
D = Bottom
E = Bottom Left
F = Top Left
G = Center
N = No Connection on Drain

      IC2         IC1  
D  01234567 D  01234567
L  CEDNBFAG L  DECNGAFB
0  11101110 0  11100111
1  10001000 1  00100001
2  01101011 2  11001101
3  10101011 3  10101101
4  10001101 4  00101011
5  10100111 5  10101110
6  11100111 6  11101110
7  10001010 7  00100101
8  11101111 8  11101111
9  10001111 9  00101111

The shift registers are cascaded by
connecting the following pins on each chip together:
13 - shift register clock pin (SRCLK),
12 - output register clock pin (RCLK),
8  - shift register clear pin (SRCLR),
9  - output enable pin

Then for each succesive higher order digit
the serial out pin (18)
is connected to the serial in pin (3)
of the next chip.

Arduino Pins
Pin 5: Data Clock
Pin 4: Output Clock
Pin 3: Clear (Active Low)
Pin 2: Serial Data
*/

#include "Seg7.h"

byte IC1[] = {
B11100111,
B00100001, 
B11001101, 
B10101101, 
B00101011, 
B10101110, 
B11101110, 
B00100101, 
B11101111, 
B00101111  
};

byte IC2[] = {
B11101110,
B10001000, 
B01101011, 
B10101011, 
B10001101, 
B10100111, 
B11100111, 
B10001010, 
B11101111, 
B10001111  
};
//#define DEBUG
const int dataPin = 2;
const int dataClock = 5;
const int latchClock = 4;
const int dataClear = 3;
Seg7 disp(dataPin, dataClock, latchClock, dataClear);

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  pinMode(dataPin, OUTPUT);
  pinMode(dataClock,OUTPUT);
  pinMode(latchClock,OUTPUT);
  pinMode(dataClear,OUTPUT);
  
  disp.init(IC1, IC2);
  disp.clear();
}

void loop()
{
  for(int i = 0; i < 100; i++)
  {
#ifdef DEBUG
    Serial.println(i);
#endif
    disp.sendNumber(i);
    delay(500);
  }
}
