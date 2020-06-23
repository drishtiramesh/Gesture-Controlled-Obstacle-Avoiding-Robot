// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const int FLEX_PIN1 = A0; // Pin1 connected to voltage divider output
const int FLEX_PIN2 = A1; // Pin2 connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line

RH_ASK driver;
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(FLEX_PIN1, INPUT);
    pinMode(FLEX_PIN2, INPUT);
}

void loop()
{
    const char *msg;
  int flexADC1 = analogRead(FLEX_PIN1);
  int flexADC2 = analogRead(FLEX_PIN2);
  if((flexADC1<200&&flexADC1>0)&&(flexADC2<200&&flexADC2>0))
    {
       msg="a";
       driver.send((uint8_t *)msg, strlen(msg));
       driver.waitPacketSent();
       delay(200);
    }
  if((flexADC1>0&&flexADC1<200)&&(flexADC2>600&&flexADC2<1000))
  {
       msg="b";
       driver.send((uint8_t *)msg, strlen(msg));
       driver.waitPacketSent();
       delay(200);   
  }
    
  if((flexADC2>0&&flexADC2<200)&&(flexADC1>600&&flexADC1<1000))
  {
       msg="c";
       driver.send((uint8_t *)msg, strlen(msg));
       driver.waitPacketSent();
       delay(200);   
  }
  
  if((flexADC1>600&&flexADC1<1000)&&(flexADC2>600&&flexADC2<1000))
  {
       msg="d";
       driver.send((uint8_t *)msg, strlen(msg));
       driver.waitPacketSent();
       delay(200);   
  }
}