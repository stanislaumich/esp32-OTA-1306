/*To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include "SettingsWiFi.h"
#include "MyWebServer.h"
#ifndef MyTime
#include "MyTime.h"
#endif
#ifndef SettingsOled
 #include "SettingsOled.h"
#endif
#include <FS.h>
#include <EEPROM.h>

unsigned long int prevm;
unsigned long int curm;
int interval=1000;

void setup(void) {
  initOled();
  FS_init();
  addds("Start");
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");  
  //WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);
  addds("Connecting");
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.println();
    IPAddress myIP = WiFi.localIP();    
    Serial.print("My IP address: ");
    Serial.println(myIP);  
    mIP=String(myIP[0])+String(".");
    mIP=mIP+String(myIP[1])+String(".");
    mIP=mIP+String(myIP[2])+String(".");
    mIP=mIP+String(myIP[3]);
    fStr=mIP;
    initWebServer();
    fStr=mIP;
    addds("Connected.");
    Serial.println("Ready! Open http://192.168.1.233 in your browser");
  } else {addds("WiFi Failed");}
   addds("Starting UDP");
   udp.begin(localPort);
   addds("UDP started.");
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
  if(prevh<h){
    
  }
  //addds(cstr);
  //wrds(); 
}