// http://oleddisplay.squix.ch/#/home
#define SettingsOled
#include "SSD1306.h"
// #include "font_orbitum_10.h"  // очень красиво
#include "font_orbitum_10.h"
#ifndef Common
 #include "common.h"
#endif 
#define OLED_SDA    5  // pin 14
#define OLED_SDC    4  // pin 12
#define OLED_ADDR   0x3C

#define font10

#ifdef font10
#define sfy 1
#define s0y 18
#define s1y 30
#define s2y 42
#define s3y 54
#endif

#ifdef font12
#define sfy 1
#define s0y 18
#define s1y 30
#define s2y 42
#define s3y 54
#endif

SSD1306  display(0x3c, 5, 4);
String ds[4];
String mIP;
String fStr;

void initOled(void){
  display.init();
  //display.flipScreenVertically();
  //display.setFont(ArialMT_Plain_10);
  display.setFont(Orbitron_Medium_10);
  }



void wrds(void)
  {
   display.clear();  
   display.drawString(1, sfy, fStr);
   display.drawString(1, s0y, ds[0]);
   display.drawString(1, s1y, ds[1]);
   display.drawString(1, s2y, ds[2]);
   display.drawString(1, s3y, ds[3]);
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