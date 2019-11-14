/*To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <FS.h>
#ifndef Common
 #include "common.h"
#endif
#ifndef SettingsWiFi
 #include "SettingsWiFi.h"
#endif 
#ifndef MyWebServer
 #include "MyWebServer.h"
#endif
#ifndef MyTime
#include "MyTime.h"
#endif
#ifndef SettingsOled
 #include "SettingsOled.h"
#endif
 

//int interval=1000;

void setup(void) {
  Button_init();
  beep(200,2000);
  initOled();
  FS_init();
  addds("Start");
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting :-)");  
  WiFiInit();
 }

void loop(void) {  
  server.handleClient();
  /*
  curm=millis();
  if (curm-prevm>interval){
   char cstr[16];
   sprintf(cstr, "%010d", curm);
   prevm=curm;  
  }
  */
  //delay(1);
  clok();
  if (millis()>screencur+screentimeout){
   screenoff();
  }
}