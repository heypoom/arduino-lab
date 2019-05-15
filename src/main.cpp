#include "Arduino.h"

#define BUTTON_BUILTIN 2
#define LED_BUILTIN 13

static const int DELAY = 500;

String text;

enum LEDState {
    ON,
    OFF,
    BLINK,
};

LEDState ledState;
LEDState _currentLEDState;

LEDState nextLEDState() {
  if (ledState == ON) return BLINK;
  if (ledState == BLINK) return OFF;
  if (ledState == OFF) return ON;

  return ON;
}

static const LEDState stringToLEDState(String state) {
  state.trim();
  state.toLowerCase();

  if (state == "on") return ON;
  if (state == "off") return OFF;
  if (state == "blink") return BLINK;

  return OFF;
}

void updateLED() {
  if (ledState == BLINK) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(DELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(DELAY);
    return;
  }

  if (_currentLEDState == ledState) return;

  if (ledState == ON) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(DELAY);
    _currentLEDState = ON;
    return;
  }

  if (ledState == OFF) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(DELAY);
    _currentLEDState = OFF;
  }
}

/// ----- Main Code --------

/// Setup.
void setup() {
  pinMode(BUTTON_BUILTIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  Serial.println("> Serial Active!");

  ledState = OFF;
}

int buttonState;

void setState(String state) {
  state.trim();
  Serial.println("Updating LED State to: " + state);

  ledState = stringToLEDState(text);
}

void loop() {
  buttonState = digitalRead(BUTTON_BUILTIN);

  if (buttonState == HIGH) {
    ledState = nextLEDState();
  }

  if (Serial.available() > 0) {
    text = Serial.readString();
    Serial.print("I received: ");
    Serial.println(text);

    setState(text);
  }

  updateLED();
}
