#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//SSID and Password for ESP8266
const char* ssid = "your_ssid";
const char* password = "password";

ESP8266WebServer server(80);
SoftwareSerial mySerial(4, 5); // RX, TX

int rele = 4;

void handleRoot() {
  String at_cmd = "";
  at_cmd = server.arg("AT");
  
  String full_cmd = "AT+" + at_cmd;
  char charAT[20];
  full_cmd.toCharArray(charAT, full_cmd.length());
  Serial.println("RECEIVED:");
  Serial.println(full_cmd);
  mySerial.println(full_cmd);

//  mySerial.write(charAT);
  delay(500);

  String content = "";
  char character;
//
//  if (mySerial.available()) {
//      server.send(200, "text/plain", mySerial.readString());
//  }
//  
  server.send(200, "text/plain", "hello");
}

void setup() {
//  pinMode(rele, OUTPUT);

    Serial.begin(9600);
    mySerial.begin(9600);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP(); //Get IP address
    Serial.print("HotSpt IP:");
    Serial.println(myIP);

    server.on("/", handleRoot);      //Which routine to handle at root location
 
    server.begin();                  //Start server
    Serial.println("HTTP server started");
    

    Serial.println("Starting the gsm and gps communication");
    mySerial.println("AT");
    delay(2000);
    mySerial.println("AT+CGNSPWR=1");
    delay(1000);
    mySerial.println("AT+CGNSSEQ=GGA");
    delay(1000);

    mySerial.println("AT+CGNSINF");
    delay(1000);
    Serial.println("Ready for communication");
}

void loop() {
//  digitalWrite(rele, 1);
//  delay(500);
//  digitalWrite(rele, 0);
//  delay(200);

    if (mySerial.available()) {
      Serial.write(mySerial.read());
    }
    
    if (Serial.available()) {
      mySerial.write(Serial.read());
    }

    server.handleClient();

}
