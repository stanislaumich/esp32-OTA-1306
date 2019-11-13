#define SettingsOled
#include "SSD1306.h"
#ifndef Common
 #include "common.h"
#endif 
#define OLED_SDA    5  // pin 14
#define OLED_SDC    4  // pin 12
#define OLED_ADDR   0x3C

SSD1306  display(0x3c, 5, 4);
String ds[4];
String mIP;
String fStr;

void initOled(void){
  display.init();
  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  }



void wrds(void)
  {
   display.clear();  
   display.drawString(1, 1, fStr);
   display.drawString(1, 18, ds[0]);
   display.drawString(1, 30, ds[1]);
   display.drawString(1, 42, ds[2]);
   display.drawString(1, 54, ds[3]);
   display.display(); 
  }
void addds(String qq){
  ds[0]=ds[1];
  ds[1]=ds[2];
  ds[2]=ds[3];
  ds[3]=qq;
  wrds();
 }
void insds(int pos,String qq){
  ds[pos]=qq;
  wrds();
 } 
void clrscr(void){
 display.clear();
 }    