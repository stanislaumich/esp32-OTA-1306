
#include <WebServer.h>
#include <Update.h>
#include "SPIFFS.h"
#include "SettingsOled.h"
#include <EEPROM.h>
#include "MyTime.h"

WebServer server(80);
File fsUploadFile;
String XML;
const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
//////////////////////////////////////////////

void FS_init(void){ 
  SPIFFS.begin();
  addds("SPIFFS.begin()");  
  }

String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
 }


bool handleFileRead(String path) {
  
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
 }

void handleFileUpload() {
  if (server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile)
      fsUploadFile.close();
  }
 }

void handleFileDelete() {
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
 }
void handleFileCreate() {
  if (server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if (file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
 server.send(200, "text/plain", "");
  path = String();
  
 }


void handleFileList() {
  addds("File list");
  String dirname ="\/";
  //int levels = 2;
  String output = "[";
  output +="Listing directory: "+ dirname;
  output +="\r\n ";
    File root = SPIFFS.open(dirname);
    if(!root){
        output +="- failed to open directory";
        return;
    }
    if(!root.isDirectory()){
        output +=" - not a directory";
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            output +="  DIR : ";
            output +=file.name();
            /*if(levels){
                listDir(SPIFFS, file.name(), levels -1);
            }*/
        } else {
            output +="  FILE: ";
            output +=file.name();
            output +="\tSIZE: ";
            output +=file.size();
            output +="\r\n ";
        }
        file = root.openNextFile();
    }
  output += "]";  
 server.send(200, "text/json", output);  
 }


String millis2time(){
  String Time="";
  unsigned long ss;
  byte mm,hh;
  ss=millis()/1000;
  hh=ss/3600;
  mm=(ss-hh*3600)/60;
  ss=(ss-hh*3600)-mm*60;
  if(hh<10)Time+="0";
  Time+=(String)hh+":";
  if(mm<10)Time+="0";
  Time+=(String)mm+":";
  if(ss<10)Time+="0";
  Time+=(String)ss;
  return Time;
 }


String alert_h(){
  String Time ="";
  byte m,h;
  EEPROM.get(0,h);
  EEPROM.get(2,m);
  Time+= (String)h+":";
  Time+= (String)m; 
  return Time;
  }

String XmlTime(void) {
   String Time ="";
   uint16_t m = ( ntp_time / 60 ) % 60;
   uint16_t h = ( ntp_time / 3600 ) % 24;
   Time+= (String)h+":";
   Time+= (String)m; 
   return Time;
 }
 
 void handle_Time() {
  int h = server.arg("h").toInt();
  int m = server.arg("m").toInt();
  String Time ="";
  Time+= (String)h+":";
  Time+= (String)m; 
  Serial.write(Time.c_str());
  EEPROM.put(0, h);
  EEPROM.put(2, m);
  EEPROM.commit();
  Serial.write("Write alert");
  EEPROM.get(0,h);
  EEPROM.get(2,m);
  Time="";
  Time+= (String)h+":";
  Time+= (String)m; 
  Serial.write(Time.c_str());
}

void buildXML(){
  XML="<?xml version='1.0'?>";
  XML+="<Donnees>"; 
    XML+="<response>";
    XML+=millis2time();
    XML+="</response>";
    XML+="<alert_time>";
    XML+=alert_h();
    XML+="</alert_time>";
    XML+="<time>";
    XML+=XmlTime();
    XML+="</time>";
  XML+="</Donnees>"; 
}
void handleXML(){
  buildXML();
  server.send(200,"text/xml",XML);
}
void initWebServer(void){
  addds("initWebServer");
  server.on("/xml",handleXML);
  server.on("/list", HTTP_GET, handleFileList);
  server.on("/Time", HTTP_GET, handle_Time);
  /*
  server.on("/test", HTTP_GET, []() {
  //загрузка редактора editor
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  */
  //Создание файла
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //Удаление файла
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []() {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

   server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");      
  });
  
    server.on("/update", HTTP_POST, []() {      
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Update: %s\n", upload.filename.c_str());
        fStr="UPDATING.....";
        addds(upload.filename.c_str());
        addds("upload.filename.c_str()");
        addds(upload.filename.c_str());
        addds(upload.filename.c_str());
        wrds();
        if (!Update.begin()) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      } else {
        Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
      }
    });
    
    /*
    server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
      Serial.write("Not Found: ");
      String s=server.uri();
      Serial.write(s.c_str());
    });*/
    server.begin();
    addds("begin WebServer");
 }