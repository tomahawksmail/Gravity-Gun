#include <SoftwareSerial.h>

// Buttons
const int buttonLeft = 2;
const int buttonRight = 3;

// LEDs
const int blueLED = 5;
const int group1LEDs[] = {4, 5, 6, 7, 8, 9};
const int group2LED = 12;

// Sound module JQ6500
SoftwareSerial mp3(10, 11); // TX=10, RX=11

// States
bool leftActive = false;
bool rightActive = false;

void setup() {
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);

  pinMode(blueLED, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(group1LEDs[i], OUTPUT);
  }
  pinMode(group2LED, OUTPUT);

  mp3.begin(9600);

  // Blink blue LED 5 times at startup
  for (int i = 0; i < 5; i++) {
    digitalWrite(blueLED, HIGH);
    delay(300);
    digitalWrite(blueLED, LOW);
    delay(300);
  }
}

void loop() {
  // Read buttons (active LOW)
  if (digitalRead(buttonLeft) == LOW) {
    leftActive = true;
    rightActive = false;
    playSound1();
  }
  if (digitalRead(buttonRight) == LOW) {
    rightActive = true;
    leftActive = false;
    playSound2();
  }

  if (leftActive) {
    group1Pattern();
  }

  if (rightActive) {
    group2Fade();
  }
}

// ---- Functions ----

// Group1 round blinking
void group1Pattern() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(group1LEDs[i], HIGH);
    delay(200);
    digitalWrite(group1LEDs[i], LOW);
  }
}

// Group2 PWM fading
void group2Fade() {
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(group2LED, brightness);
    delay(5);
    if (!rightActive) return;
  }
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(group2LED, brightness);
    delay(5);
    if (!rightActive) return;
  }
}

// Play sound1 in repeat
void playSound1() {
  static bool playing1 = false;
  if (!playing1) {
    // JQ6500 Play track 1
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0x01); // file 1
    mp3.write(0xEF);
    playing1 = true;
  }
}

// Play sound2 in repeat
void playSound2() {
  static bool playing2 = false;
  if (!playing2) {
    // JQ6500 Play track 2
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0x02); // file 2
    mp3.write(0xEF);
    playing2 = true;
  }
}
