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
const int group1LEDs[] = {4, 5, 6, 7, 8, 9};
const int RingLED = 12;
const int numGroup1LEDs = sizeof(group1LEDs) / sizeof(group1LEDs[0]);

// For blinking effect
unsigned long previousMillis = 0;
const long blinkInterval = 300;  // ms
bool ledState = false;
bool blinkActive = false;

void setup() {
  mySerial.begin(9600);
  mp3.reset();
  mp3.setLoopMode(MP3_LOOP_NONE);

  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);

  pinMode(blueLED, OUTPUT);
  pinMode(RingLED, OUTPUT);

  for (int i = 0; i < numGroup1LEDs; i++) {
    pinMode(group1LEDs[i], OUTPUT);
  }
}

void loop() {
  if (digitalRead(buttonLeft) == LOW) {
    LeftButton();
  } else if (digitalRead(buttonRight) == LOW) {
    RightButton();
  } else {
    StopAll();
  }

  // Handle blinking LEDs without blocking
  if (blinkActive) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      for (int i = 0; i < numGroup1LEDs; i++) {
        digitalWrite(group1LEDs[i], ledState ? HIGH : LOW);
      }
    }
  }
}

void LeftButton() {
  mp3.setVolume(20);  // JQ6500 max is 30, not 150
  mp3.playFileByIndexNumber(2);
  digitalWrite(blueLED, HIGH);
  blinkActive = false;  // only steady LED
}

void RightButton() {
  mp3.setVolume(20);
  mp3.playFileByIndexNumber(1);
  blinkActive = true;  // start blinking LEDs
}

void StopAll() {
  digitalWrite(blueLED, LOW);
  for (int i = 0; i < numGroup1LEDs; i++) {
    digitalWrite(group1LEDs[i], LOW);
  }
  blinkActive = false;
}
