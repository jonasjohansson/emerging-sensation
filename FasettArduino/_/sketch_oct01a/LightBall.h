/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef LightBall_h
#define LightBall_h

#include "Arduino.h"
#include<FastLED.h>
class LightBall
{
  public:
    LightBall(CRGB leds, int offset, int steps, int inc);
    void setColor(int r, int g, int b);
  private:
    int _leds;
    int _offset;
    int _steps;
    int _inc;
};

#endif
