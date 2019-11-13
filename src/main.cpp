/*To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
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
 
#include <FS.h>
//#include <EEPROM.h>

unsigned long int prevm;
unsigned long int curm;
unsigned long int tm;

int interval=1000;

void setup(void) {
  initOled();
  FS_init();
  addds("Start");
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");  
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid1, password1);
  addds("Try connect...");
  addds(ssid1);
  tm=millis();
  ////////////////////////////////
  while ((WiFi.waitForConnectResult() != WL_CONNECTED) and (millis()<tm+ WiFiTimeout)){

  }
  

  if (!WiFi.isConnected()){
    tm=millis();
    //WiFi.config(ip, gateway, subnet, dns1, dns2);
    WiFi.begin(ssid2, password2);
    addds("Try connect...");
    addds(ssid2);
    while ((WiFi.waitForConnectResult() != WL_CONNECTED) and (millis()<tm+ WiFiTimeout)){

    } 
   }
///////////////////////////////

   if (WiFi.isConnected()){
    IPAddress myIP = WiFi.localIP();    
    Serial.print("My IP address: ");
    Serial.println(myIP);  
    mIP=String(myIP[0])+String(".");
    mIP=mIP+String(myIP[1])+String(".");
    mIP=mIP+String(myIP[2])+String(".");
    mIP=mIP+String(myIP[3]);
    fStr=mIP+" "+getSsidPass("SSID");
    initWebServer();
    addds("Connected.");
    Serial.println("Ready! Open http://192.168.1.233 in your browser");
    addds("Starting UDP");
    udp.begin(localPort);
    addds("UDP started.");
   }
   else{
     clrscr();
     fStr="ERROR";
     addds("WiFi Failed.");
   }
//0 +
 //12 -
 pinMode(0,OUTPUT);
 pinMode(12,OUTPUT);
 digitalWrite(12,LOW);
 digitalWrite(0,LOW);
 unsigned long h;
 h=millis();
 while (millis()-h<300){
 digitalWrite(0,HIGH);
 delay(2);
 digitalWrite(0,LOW);
 delay(2);
 }

 }

void loop(void) {  
  server.handleClient();
  curm=millis();
  if (curm-prevm>interval){
   char cstr[16];
   sprintf(cstr, "%010d", curm);
   prevm=curm;  
  }
  delay(1);
  clok();
  if (millis()>screencur+screentimeout){
   screenoff();
  }
}