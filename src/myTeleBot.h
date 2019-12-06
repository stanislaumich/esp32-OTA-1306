#ifndef MyTeleBot
#define MyTeleBot
#ifndef common
  #include "common.h"
 #endif
#ifndef myTime
  #include "myTime.h"
 #endif 
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "UniversalTelegramBot.h"
#define myTele "357390016"

#define BOTtoken "852912728:AAFxGJGyirIIE4vMMrWXwW1l0M2N6Ubigq0"
//#define BOTname "Lz42Esp32Clock"
//#define BOTusername "Lz42Esp32ClockBot"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client); 
 
int Bot_mtbs = 1000; 
long Bot_lasttime;   
bool Start = false;

const int ledPin = 13;
int ledStatus = 0; 

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/b0") {
      Button(0);
      bot.sendMessage(chat_id, "+Button 0", "");
    }

    if (text == "/b1") {
      Button(1);
      bot.sendMessage(chat_id, "+Button 1", "");
    }

    if (text == "/b2") {
      Button(2);
      bot.sendMessage(chat_id, "+Button 2", "");
    }

    if (text.indexOf("/bud")==0) {
      String sa = getValue(text,' ',1);
      String mess="\n";
      if (sa=="?"){
        int tph = getBud(0);
        int tpm = getBud(1);        
        mess+=String(tph)+":"+String(tpm);
      }else{
      String sh = getValue(text,' ',1);
      String sm = getValue(text,' ',2);
      setBud(sh.toInt(),sm.toInt());
      mess+="+Установлен будильник";
      }
      bot.sendMessage(chat_id, mess, "");
    }

    if (text == "/beep") {
      beep(250,125);
      bot.sendMessage(chat_id, "+I'm beeping", "");
    }

    if (text == "/status") {
      String mess="";
      mess+="+Bu 0 - "+String(getButton(0))+"\n";
      mess+="+Bu 1 - "+String(getButton(1))+"\n";
      mess+="+Bu 2 - "+String(getButton(2))+"\n";
      bot.sendMessage(chat_id, mess, "");
    }
     
    if (text == "/on") {
      String mess="I am ON";
      myON=true;
      bot.sendMessage(chat_id, mess, "");
    }
    if (text == "/u") {
      String mess="Uptime: "+millis2time();      
      bot.sendMessage(chat_id, mess, "");
    } 

    millis2time();
    if (text == "/off") {
      String mess="I am OFF";
      myON=false;
      bot.sendMessage(chat_id, mess, "");
    } 
    if (text == "/start") {
      String welcome = "ESP32 Home 1306 Clock Bot, " + from_name + ".\n";
      welcome += "/b1 : to switch the button N\n";
      welcome += "/u : Uptime\n";
      welcome += "/beep : to beep\n";
      welcome += "/bud ? : to see ringer\n";
      welcome += "/bud 18 00 : to set ringer\n";
      welcome += "/status : Returns current status of buttons\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
 } 

void MyTeleBotInit(void){
  //client.setInsecure(); 
 } 

void goBot(void){
    if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  } 
 }



#endif