#define BLYNK_TEMPLATE_ID "TMPLPkIdMTpx"
#define BLYNK_TEMPLATE_NAME "GAS SENSOR"
#define BLYNK_AUTH_TOKEN "jzNMQohOT2YjzLp4zSnop14OB7UNrZ0F"
#define LINE_TOKEN  "65ieePaS2rkgFM7zS4NWAsJonnoSOLlFL4iykhRJW3Q"

#include <SoftwareSerial.h> 
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include "MQ7.h"
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>

int lock=0;
const int redLedPin = D1;
const int yellowLedPin = D2;
const int greenLedPin = D3;
const int buzzerPin = D5;
const int sensorPin = A0;

char auth[] = "jzNMQohOT2YjzLp4zSnop14OB7UNrZ0F";

MQ7 mq7(A0, 5.0);

BlynkTimer timer;


void updateLCD() {
  float ppm = mq7.getPPM();
  String quality = "";

  if (ppm < 15) {
    quality = "Safe";
  } else if (ppm <25 ) {
    quality = "Less risk";
  } else if (ppm < 100) {
    quality = "High danger";
  } else {
    quality = "extremely danger";
  }

  Blynk.virtualWrite(V2, quality);
}

void setup() {
   Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion()); 

  LINE.setToken(LINE_TOKEN);

  Blynk.begin(auth, "Manee", "0829680775");
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  timer.setInterval(1000L, updateLCD);
}



void loop() {
  int sensorValue = analogRead(sensorPin);
  float ppm = mq7.getPPM();

  Serial.print("CO level: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  

  Blynk.virtualWrite(V0, ppm);
  Blynk.virtualWrite(V1, ppm);

  if (ppm < 15 ) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    
   

  } else if (ppm <25 ) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 500, 500);
    

  } else if (ppm < 100 ) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 1000, 500);

  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 2000, 500); 
    LINE.notify("อันตรายสูง !!!! ออกจากพื้นที่โดยด่วน");
    LINE.notifySticker(789,10890);
    
  }


  Blynk.run();
  timer.run();
}


