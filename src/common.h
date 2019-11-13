#define Common
#ifndef SettingsOled
 #include "SettingsOled.h"
#endif

void Button_init(){
  
  /*pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);*/
 }
void Button(int state){
 switch (state) {
    case 2:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, LOW);
      //digitalWrite(rele3, HIGH);
      addds("State 2");
      break;
    case 1:
      //digitalWrite(rele1, LOW);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 1");
      break;
    case 0:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 0");
      break;
  }

} 