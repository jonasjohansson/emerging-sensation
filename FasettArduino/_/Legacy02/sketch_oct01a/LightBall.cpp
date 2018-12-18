/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Lightball.h"
#include<FastLED.h>

LightBall::LightBall(CRGB leds, int offset, int steps, int inc)
{
  _offset = offset;
  _steps = steps;
  _inc = inc;
  _leds = leds;
}

void LightBall::setColor(int r, int g, int b)
{
  for (uint8_t i = 0; i < _steps; i+=_inc) {
    int index = _offset + i;
    _leds[index] = CRGB(r, g, b);
    FastLED.show();
  }
}
