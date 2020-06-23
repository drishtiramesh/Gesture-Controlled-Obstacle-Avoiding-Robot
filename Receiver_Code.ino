#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
// RH_ASK driver(2000, 2, 4, 5); // ESP8266: do not use pin 11

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
int leftForward=2;
int rightForward=4;
int leftBackward=3;
int rightBackward=5;

void setup() {
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(leftForward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightBackward, OUTPUT);

}

void loop() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    if(distance>40)
      {
              if (driver.recv(buf, &buflen)) // Non-blocking
                {
                    if(*buf=='a')
                      forward();
                    else if(*buf=='b')
                      left();
                    else if(*buf=='c')
                      right();
                    else if(*buf=='d')
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
