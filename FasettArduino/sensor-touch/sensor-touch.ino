/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Update 2014 - TMRh20
 */

/**
 * Simplest possible example of using RF24Network 
 *
 * TRANSMITTER NODE
 * Every 2 seconds, send a payload to the receiver node.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


const uint16_t server_node = 00;       // Address of our server node in Octal format 
const uint16_t this_node = 01;       // Address of our node in Octal format

uint16_t sensorPin = 4;
uint16_t lastTouch=0;


RF24 radio(7,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio


const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct payload_t {                  // Structure of our payload
  uint16_t value;
};

void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_tx/");

  pinMode(sensorPin, INPUT);
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop() {
  
  network.update();                          // Check the network regularly

  uint16_t newTouch = digitalRead(sensorPin);
  if(newTouch != lastTouch) {
    lastTouch = newTouch;
    payload_t payload = { newTouch };
    RF24NetworkHeader header(/*to node*/ server_node);
    network.write(header,&payload,sizeof(payload));
  }
  delay(20);
 
}


/*
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
*/
