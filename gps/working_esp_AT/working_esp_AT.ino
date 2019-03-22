#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

int rele = 4;

void setup() {
//  pinMode(rele, OUTPUT);
  
    Serial.begin(9600);
    mySerial.begin(9600);

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

}
