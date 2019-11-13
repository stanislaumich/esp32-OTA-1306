#define SettingsWiFi
#include <WiFi.h>
#include <WiFiClient.h>
#ifndef Common
 #include "common.h"
#endif
#include <esp_wifi.h> 
//const char* host = "esp32-webupdate";
const char* ssid2 = "SAN";
const char* password2 = "37212628";
const char* ssid1 = "ZTE54";
const char* password1 = "121211119";
const int WiFiTimeout = 5000;// ms

IPAddress ip(192,168,1,233);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);

String getSsidPass( String s )
{
  String val = "NONE";  // if invalid, returns "NONE"
  s.toUpperCase();
  if( s.compareTo("SSID") == 0 )
  {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    val = String(reinterpret_cast<const char*>(conf.sta.ssid));
  }/*
  if( s.compareTo("PASS") == 0 )
  {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    val = String(reinterpret_cast<const char*>(conf.sta.password));
  }*/
  return val;
}