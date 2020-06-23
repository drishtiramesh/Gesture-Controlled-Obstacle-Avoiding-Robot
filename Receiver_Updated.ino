#include <VirtualWire.h>
#include <VirtualWire_Config.h>


//const int led_pin = 6;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
 int trigpin=9;
 int echopin=10;
// defines variables
int leftForward=2;
int rightForward=4;
int leftBackward=3;
int rightBackward=5;

void setup()
{
    //delay(1000);
    // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_ptt_pin(transmit_en_pin);
    
   Serial.begin(9600);
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);

    pinMode(leftForward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
    pinMode(6,OUTPUT);
    digitalWrite(6,HIGH);
    pinMode(7,OUTPUT);
    digitalWrite(7,LOW);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec  
    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{   
    uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
  int duration;
  float distance;
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
 // delayMicroseconds(2);
  duration=pulseIn(echopin,HIGH);
  distance = (duration/29.1/2);
  Serial.println(distance);
    if(distance>15)
    {
        if (vw_get_message(buf, &buflen)) // Non-blocking
        {
             digitalWrite(leftForward, LOW);
             digitalWrite(rightForward, LOW);
             digitalWrite(leftBackward, LOW);
             digitalWrite(rightBackward, LOW);
             Serial.println(char(buf[0]));
             if(buf[0]=='a')
                 forward();
               else if(buf[0]=='b')
                   right();
              else if(buf[0]=='c')
                   left();
              else if(buf[0]=='d')
                   stp();
          }                
      }
      else
        {
         stp();
      delay(100);
          right();
      delay(100);
        }
       delay(200);
    }
void forward()
{
   digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
}
void left()
{ 
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightBackward, LOW);
}
void right()
{
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, HIGH);
}

void stp()
{
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightBackward, LOW);
}
