#define Common
#ifndef SettingsOled
 #include "SettingsOled.h"
#endif

int XMLb0;
int XMLb1;
int XMLb2;
#define pinp 14
#define pinn 15
void beep(int t1,int t2){
 unsigned long h;
  h=millis();
  while (millis()-h<t1){
   digitalWrite(pinp,HIGH);
   delayMicroseconds(t2);
   digitalWrite(pinp,LOW);
   delayMicroseconds(t2);
  }
 }

void Button_init(void){
  pinMode(pinp,OUTPUT);
  pinMode(pinn,OUTPUT);
  digitalWrite(pinp,LOW);
  digitalWrite(pinn,LOW); 
 }
void Button(int state){
 switch (state) {
    case 2:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, LOW);
      //digitalWrite(rele3, HIGH);
      addds("State 2");
      XMLb2?XMLb2=0:XMLb2=1;
      break;
    case 1:
      //digitalWrite(rele1, LOW);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 1");
      XMLb1?XMLb1=0:XMLb1=1;
      break;
    case 0:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 0");
      XMLb0?XMLb0=0:XMLb0=1;
      break;
  }

 } 