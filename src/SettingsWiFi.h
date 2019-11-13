#define SettingsWiFi
#include <WiFi.h>
#include <WiFiClient.h>
#ifndef Common
 #include "common.h"
#endif 
//const char* host = "esp32-webupdate";
const char* ssid = "SAN";
const char* password = "37212628";

//const char* ssid = "ZTE54";
//const char* password = "121211119";

IPAddress ip(192,168,1,233);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);