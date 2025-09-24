#include <Arduino.h>
#include <SoftwareSerial.h>
#include <JQ6500_Serial.h>

// Buttons
const int buttonLeft = 2;
const int buttonRight = 3;

// Setup Libraries
SoftwareSerial mySerial(10, 11);
JQ6500_Serial mp3(mySerial);


// LEDs
const int blueLED = A3;
const int group1LEDs[] = { 4, 5, 6, 7, 8, 9 };
const int RingLED = 12;


void setup() {
  mySerial.begin(9600);
  mp3.reset();
  mp3.setLoopMode(MP3_LOOP_NONE);

  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);

  pinMode(blueLED, OUTPUT);
  pinMode(RingLED, OUTPUT);
  pinMode(group1LEDs, OUTPUT);


}

void loop() {
  if (mp3.getStatus() != MP3_STATUS_PLAYING) {

    if (digitalRead(buttonLeft) == LOW) {
      LeftButton();
    } else {

      StopAll();  // Turn LED OFF
    }



    if (digitalRead(buttonRight) == LOW) {
      RightButton();
    }
  }
}


void LeftButton() {
  mp3.setVolume(150);
  mp3.playFileByIndexNumber(2);
  digitalWrite(blueLED, HIGH);
}

void RightButton() {
  mp3.setVolume(140);
  mp3.playFileByIndexNumber(1);
  digitalWrite(group1LEDs, HIGH);
  delay(20);
  digitalWrite(group1LEDs, LOW);
  
}

void StopAll() {
  digitalWrite(blueLED, LOW);
  digitalWrite(group1LEDs, LOW);
}
