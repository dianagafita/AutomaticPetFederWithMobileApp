#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 
#include <ESP8266mDNS.h> 
#include <Arduino.h>
#include "HX711.h"

const int sensorDT_1 = 12;
const int sensorSCK_1 = 13;
const int sensorDT_2 = 4;
const int sensorSCK_2 = 5;
const int sensorDT_3 = 0;
const int sensorSCK_3 = 14;
const int water = A0;
HX711 scale1;
HX711 scale2;
HX711 scale3;
MDNSResponder mdns;
const char* wifi = "iPhone";
const char* pass = "1234512345";
ESP8266WebServer server (80);
String webpage ="";

unsigned long last = 0; 
const unsigned long readInt = 6000; 

void setup(void) {

  scale1.begin(sensorDT_1, sensorSCK_1);
  scale2.begin(sensorDT_2, sensorSCK_2);
  scale3.begin(sensorDT_3, sensorSCK_3);
  delay(1000);
  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial);
  WiFi.begin(wifi,pass);
  Serial.println("");
  while(WiFi.status() != WL_CONNECTED) {
   delay (500);
   Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi: ");
  Serial.println(wifi);
  Serial.print("IP to use: ");
  Serial.println(WiFi.localIP());
  if(mdns.begin("esp8266",WiFi.localIP())){
    Serial.println("MDNS Responder has started");
  }
server.on("/read1", []() {
    float scale1read = scale1.get_units(5) - 534.5;
    char result1[10] = "";
    dtostrf(scale1read, 0 ,1, result1);
    webpage = "";  
    webpage += result1;
    Serial.print("BOL APA: ");
    Serial.println(result1);
    server.send(200, "text/html", webpage);
    delay (1);
});
server.on("/read2", []() {
    float scale2read = scale2.get_units(5) - 994.5;
    char result2[10] = "";
    dtostrf(scale2read, 0 ,1, result2);
    webpage = ""; 
    webpage += result2;
    Serial.print("CONTAINER MANCARE: ");
    Serial.println(result2);
    server.send(200, "text/html", webpage);
    delay (1);
});
server.on("/read3", []() {
    float scale3read = scale3.get_units(5)-537.11;
    char result3[14] = "";
    dtostrf(scale3read, 0 ,1, result3);
    webpage = ""; 
    webpage += result3;
    Serial.print("BOL MANCARE ");
    Serial.println(result3);
    server.send(200, "text/html", webpage);
    delay (1);
});
server.on("/read4", []() {
    float waterread = analogRead(water);
    char result4[14] = "";
    dtostrf(waterread, 0 ,1, result4);
    webpage = "";   
    webpage += result4;
    Serial.print("NIVEL CONTAINER APA ");
    Serial.println(result4);
    server.send(200, "text/html", webpage);
    delay (1);
});
server.on("/waterpump/on", []() {
    char str = '1'; 
    Serial1.println(str);   
    server.send(200, "text/plain", "Water pump turned on");
  });
server.on("/waterpump/off", []() {
    char str = '0'; 
    Serial1.println(str);      
    server.send(200, "text/plain", "Water pump turned off");
  });
server.on("/servo/on", []() {
    char str = '2'; 
    Serial1.println(str);   
    server.send(200, "text/plain", "Water pump turned on");
  });
server.on("/servo/off", []() {
    char str = '3'; 
    Serial1.println(str);      
    server.send(200, "text/plain", "Water pump turned off");
  });
  delay (1000);
  server.begin();
  Serial.println("HTTP Server started");

   float initialValue = 0.0;
   initialValue = scale1.get_units(10); 
   Serial.println(initialValue);
   scale1.set_scale(-760.16);
   scale2.set_scale(763.40);
   scale3.set_scale(-479.29);
  Serial.println("Readings:");
}

void loop(void)
 {
 server.handleClient();
 unsigned long currentTime = millis();
   if (currentTime - last >= readInt) {
      last = currentTime; 
  Serial.print("Bol apa:\t");
  Serial.print(scale1.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale1.get_units(10), 5);
  Serial.print("Container mancare:\t");
  Serial.print(scale2.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale2.get_units(10), 5);
  Serial.print("Bol mancare:\t");
  Serial.print(scale3.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale3.get_units(10), 5);  
  Serial.print("Nivel container apa:\t");
  Serial.println(analogRead(water));  
}}


