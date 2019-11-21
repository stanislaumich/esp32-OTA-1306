#ifndef common
#define common
#ifndef SettingsOled
 #include "SettingsOled.h"
#endif
#include <Preferences.h>

Preferences prefs;

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
      addds("State 2 switched");
      XMLb2?XMLb2=0:XMLb2=1;
      break;
    case 1:
      //digitalWrite(rele1, LOW);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 1 switched");
      XMLb1?XMLb1=0:XMLb1=1;
      break;
    case 0:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      addds("State 0 switched");
      XMLb0?XMLb0=0:XMLb0=1;
      break;
  }

 }
String getValue(String data, char separator, int index){
  // String part01 = getValue(application_command,';',0); 
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
 }  

int getButton(int b){
  switch(b){
   case 0: return 0;
     break;
   case 1: return 1;
     break;
   case 2: return 2;
     break;    
   default: break;
   }  

  return 0;//EEPROM.read(10+b);
  }


int getBud(int p){
  if (p==0){   
   return prefs.getInt("alarm_h", 0);
  }
  if (p==1){
   return prefs.getInt("alarm_m",0);
  }
 }

void setBud(int ph,int pm){
  size_t q1 = prefs.putInt("alarm_h", ph);
  size_t q2 = prefs.putInt("alarm_m", pm);
 } 

#endif  