#include <Arduino.h>
/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include "SettingsWiFi.h"
#include "MyWebServer.h"
//#include "SSD1306.h"
#include "SettingsOled.h"


void setup(void) {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  initOled();

  



  //WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP_STA);

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.println();
    IPAddress myIP = WiFi.localIP();
    //Serial.println(WiFi.localIP()); WiFi.softAPIP();
    Serial.print("My IP address: ");
    Serial.println(myIP);
    
    initWebServer();

  display.drawString(1, 1, String(millis()%10000));
  display.drawString(1, 25, String(millis()%10000));
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 1, String(millis()%10000));
  display.drawString(128, 25, String(millis()%10000)); 
   

    Serial.println("Ready! Open http://192.168.1.233 in your browser");
  } else {
    Serial.println("WiFi Failed");
  }
}

void loop(void) {
  server.handleClient();
  display.display(); 
  delay(1);
}