/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

byte sensorID = 1;
byte sensorPin = 4;


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  
}

uint16_t lastTouch=0;

void loop() {
  uint16_t newTouch = digitalRead(sensorPin);
  if(newTouch != lastTouch) {
    lastTouch = newTouch;
    byte data[2]={sensorID, newTouch};
    radio.write(&data, sizeof(data));
  }
  delay(20);
}

