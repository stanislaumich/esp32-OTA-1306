#define MyTime
#include "WiFiClient.h"
#include <Preferences.h>
#ifndef Common
 #include "common.h"
#endif 

unsigned long localPort = 2390;  
unsigned long ntp_time = 0;
long  t_correct        = 0;
unsigned long cur_ms   = 0;
unsigned long ms1      = 0;
unsigned long ms2      = 10000000UL;
unsigned long t_cur    = 0;
bool          points   = true;
unsigned int err_count = 0;
int gh;
int gm;
#define TIMEZONE 3

Preferences prefs;
IPAddress timeServerIP; 
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[NTP_PACKET_SIZE]; 
WiFiUDP udp;


  // Каждые 0.5 секунды выдаем время
void DisplayTime(void) {
  uint16_t m = ( ntp_time / 60 ) % 60;
  uint16_t h = ( ntp_time / 3600 ) % 24;
  int th;
  int tm;
  size_t q1 = prefs.getInt("alarm_h", th);
  size_t q2 = prefs.getInt("alarm_m", tm);

  if (th == h && tm == m ) {
    addds("ALARMA!!!!");
    Serial.write("ALARMA!!!!");
  }
  if (gm!=m){
    String Time ="";
    if (h<10){Time+= "0"+(String)h+":";}else{Time+= (String)h+":";}
    if (m<10){Time+= "0"+(String)m;}else{Time+= (String)m;} 
    addds(Time);    
    }
  gh=h;
  gm=m;
 }


unsigned long sendNTPpacket(IPAddress& address) {
  Serial.println("sending NTP packet...");
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  udp.beginPacket(address, 123);
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();  
 }


bool GetNTP(void) {
  WiFi.hostByName(ntpServerName, timeServerIP);
  sendNTPpacket(timeServerIP);
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("No packet yet");
    return false;
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // Читаем пакет в буфер
    udp.read(packetBuffer, NTP_PACKET_SIZE);
    // 4 байта начиная с 40-го сождержат таймстамп времени - число секунд
    // от 01.01.1900
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // Конвертируем два слова в переменную long
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Конвертируем в UNIX-таймстамп (число секунд от 01.01.1970
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    // Делаем поправку на местную тайм-зону
    ntp_time = epoch + TIMEZONE * 3600;
    Serial.print("Unix time = ");
    Serial.println(ntp_time);
  }
  return true;
 }


void clok() {
  cur_ms       = millis();
  t_cur        = cur_ms / 1000;
  // Каждые 60 секунд считываем время в интернете
  if ( cur_ms < ms2 || (cur_ms - ms2) > 60000 ) {
    err_count++;
    // Делаем три  попытки синхронизации с интернетом
    if ( GetNTP() ) {
      ms2       = cur_ms;
      err_count = 0;
      t_correct = ntp_time - t_cur;
    }
  }
  if ( cur_ms < ms1 || (cur_ms - ms1) > 500 ) {
    ms1 = cur_ms;
    ntp_time    = t_cur + t_correct;
    DisplayTime();
    points = !points;
   }  
 }