#include <Arduino.h>/*To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include "SettingsWiFi.h"
#include "MyWebServer.h"
#ifndef SettingsOled
#include "SettingsOled.h"
#endif
#include <FS.h>
#include <EEPROM.h>


void setup(void) {
  initOled();
  FS_init();
  addds("Start");
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  
  //WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  addds("Connecting");
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.println();
    IPAddress myIP = WiFi.localIP();
    
    //Serial.println(WiFi.localIP()); WiFi.softAPIP();
    Serial.print("My IP address: ");
    Serial.println(myIP);
  
    mIP=String(myIP[0])+String(".");
    mIP=mIP+String(myIP[1])+String(".");
    mIP=mIP+String(myIP[2])+String(".");
    mIP=mIP+String(myIP[3]);
    fStr=mIP;
    initWebServer();

    display.drawString(1, 1, mIP);
  //display.setTextAlignment(TEXT_ALIGN_RIGHT);
  //display.drawString(128, 1, String(millis()%10000));
  //display.drawString(128, 25, String(millis()%10000)); 
    addds("Connected.");

    Serial.println("Ready! Open http://192.168.1.233 in your browser");
  } else {
    Serial.println("WiFi Failed");
  }
}

unsigned long int prevm;
unsigned long int curm;
int interval=1000;


void loop(void) {
  server.handleClient();
  curm=millis();
  if (curm-prevm>interval){
   //int val = hallRead();
   char cstr[16];
   //itoa(curm, cstr, 10);
   sprintf(cstr, "%010d", curm);
   addds(cstr);
   //wrds();
   prevm=curm;  
  }
  delay(1);
}