#include <VirtualWire.h>
#include <VirtualWire_Config.h>
char *msg;
const int FLEX_PIN1 = A0; // Pin1 connected to voltage divider output
const int TILT_SENS = 8; // Pin2 connected to voltage divider output
int flexADC1;
int tiltsens;

void setup() {
  vw_set_ptt_inverted(true); // Required for DR3100
     vw_set_tx_pin(12);
    vw_setup(4000);   // Bits per sec
Serial.begin(9600);    // Debugging only
pinMode(2,OUTPUT);
    digitalWrite(2,HIGH);
   
    pinMode(FLEX_PIN1, INPUT);
    pinMode(TILT_SENS, INPUT);
    pinMode(6,OUTPUT);
    digitalWrite(6,HIGH);
    pinMode(7,OUTPUT);
    digitalWrite(7,LOW);
    
    
}

void loop() {
      //const char *msg;
flexADC1 = analogRead(FLEX_PIN1);
  tiltsens = digitalRead(TILT_SENS);
  Serial.println(flexADC1);
  Serial.println(tiltsens);
  delay(500);
  /*Serial.println(flexADC2);
  delay(1000);*/
  if((flexADC1<50&&tiltsens==HIGH))
    {
      msg="a";
       vw_send((uint8_t *)msg, strlen(msg));
       vw_wait_tx();
       delay(200);
    }
  if((flexADC1>50&&tiltsens==LOW))
  {
       msg="b";
       vw_send((uint8_t *)msg, strlen(msg));
       vw_wait_tx();
       delay(200); 
  }

  
  if((flexADC1<50&&tiltsens==LOW))
  {
      msg="c";
      vw_send((uint8_t *)msg, strlen(msg));
       vw_wait_tx();
       delay(200);   
  }
  
  if((flexADC1>50)&&(tiltsens==HIGH))
  {
       msg="d";
       vw_send((uint8_t *)msg, strlen(msg));
       vw_wait_tx();
       delay(200);   
 }
}
