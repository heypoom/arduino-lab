#include "Arduino.h"

#define LED_BUILTIN 13

static const int DELAY = 500;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  Serial.println("> Serial Active!");
}

String text;

enum LEDState {
    ON,
    OFF,
    BLINK
};

LEDState ledState;
LEDState _currentLEDState;

static const LEDState stringToLEDState(String state) {
  state.trim();
  state.toLowerCase();

  if (state == "on") return ON;
  if (state == "off") return OFF;
  if (state == "blink") return BLINK;

  return OFF;
}

static const String ledStateToString(LEDState state) {
  if (state == ON) return "On";
  if (state == OFF) return "Off";
  if (state == BLINK) return "Blink";

  return "None";
}

void updateLED() {
  if (ledState == BLINK) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(DELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(DELAY);
    return;
  }

  if (ledState && _currentLEDState == ledState) return;

  Serial.println("Updating LED State to: " + ledStateToString(ledState));

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

void loop() {
  if (Serial.available() > 0) {
    text = Serial.readString();
    Serial.print("I received: ");
    Serial.println(text);

    ledState = stringToLEDState(text);
  }

  updateLED();
}
