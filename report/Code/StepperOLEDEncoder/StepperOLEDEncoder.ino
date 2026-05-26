/**
 * @file StepperOLEDEncoder.ino
 * @brief Steuerung eines Schrittmotors mit OLED-Display, Encoder, Taster und Endschalter.
 *
 * Das Programm steuert einen Schrittmotor ueber einen Motortreiber.
 * Ueber einen Drehencoder kann eine Stufe von 1 bis 10 ausgewaehlt werden.
 * Die aktuelle Stufe und der Programmstatus werden auf einem OLED-Display angezeigt.
 *
 * Mit dem Starttaster wird zuerst eine Referenzfahrt ausgefuehrt.
 * Danach bewegt sich der Schlitten entsprechend der ausgewaehlten Stufe.
 *
 * Ein Endschalter dient zur Referenzierung.
 * Ein Encoder-Taster kann zum Abbrechen verwendet werden.
 */

#include "AccelStepper.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

/**
 * @brief Interface-Typ fuer den Schrittmotortreiber.
 *
 * Der Wert 1 steht bei AccelStepper fuer einen Treiber mit STEP- und DIR-Pin.
 */
#define MOTOR_INTERFACE_TYPE 1

/** @brief Breite des OLED-Displays in Pixeln. */
#define SCREEN_WIDTH 128

/** @brief Hoehe des OLED-Displays in Pixeln. */
#define SCREEN_HEIGHT 64

/** @brief Reset-Pin des OLED-Displays. -1 bedeutet, dass kein Reset-Pin verwendet wird. */
#define OLED_RESET -1

/** @brief I2C-Adresse des OLED-Displays. */
#define SCREEN_ADDRESS 0x3C

/** @brief Richtungspin des Schrittmotortreibers. */
#define PIN_STEP_DIR 4

/** @brief STEP-Pin des Schrittmotortreibers. */
#define PIN_STEP_STEP 5

/** @brief Pin der roten LED. */
#define PIN_LED_RED 6

/** @brief Pin der gruenen LED. */
#define PIN_LED_GREEN 7

/** @brief Pin der blauen LED. */
#define PIN_LED_BLUE 8

/** @brief Pin des Starttasters. */
#define PIN_BUTTON 11

/** @brief Pin des Endschalters fuer die Referenzfahrt. */
#define PIN_ENDSTOP 12

/** @brief CLK-Pin des Drehencoders. */
#define PIN_CLK 9

/** @brief DT-Pin des Drehencoders. */
#define PIN_DT 2

/** @brief SW-Pin des Encoder-Tasters. */
#define PIN_SW 3

/**
 * @brief Schrittmotor-Objekt.
 *
 * Das Objekt steuert den Schrittmotor ueber STEP und DIR.
 */
AccelStepper stepper(MOTOR_INTERFACE_TYPE, PIN_STEP_STEP, PIN_STEP_DIR);

/**
 * @brief OLED-Display-Objekt.
 *
 * Das Display wird ueber I2C mit der Wire-Bibliothek angesteuert.
 */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * @brief Encoder-Objekt.
 *
 * Der Encoder wird verwendet, um die Betriebsstufe auszuwaehlen.
 */
Encoder encoder(PIN_DT, PIN_CLK);

/** @brief Aktueller Zustand des Starttasters. */
int buttonStatus = HIGH;

/** @brief Vorheriger Zustand des Starttasters. */
int lastButtonStatus = HIGH;

/** @brief Zeitpunkt der letzten Zustandsaenderung des Tasters. */
unsigned long lastDebounceTime = 0;

/** @brief Entprellzeit fuer Taster und Endschalter in Millisekunden. */
unsigned long debounceDelay = 50;

/** @brief Aktueller Zustand des Endschalters. */
int endstopStatus = HIGH;

/** @brief Vorheriger Zustand des Endschalters. */
int lastEndstopStatus = HIGH;

/** @brief Zeitpunkt der letzten Zustandsaenderung des Endschalters. */
unsigned long lastEndstopDebounceTime = 0;

/** @brief Aktuell ausgewaehlte Stufe. */
int stage = 1;

/**
 * @brief Geschwindigkeiten fuer die einzelnen Stufen.
 *
 * Index 0 wird fuer die Referenzfahrt bzw. Startwerte verwendet.
 * Die Stufen 1 bis 10 verwenden die Indizes 1 bis 10.
 */
int speeds[] = {
  1000,
  500,
  750,
  1000,
  1250,
  1500,
  1750,
  2000,
  2250,
  2500,
  1750
};

/**
 * @brief Beschleunigungswerte fuer die einzelnen Stufen.
 *
 * Index 0 wird fuer die Referenzfahrt bzw. Startwerte verwendet.
 * Die Stufen 1 bis 10 verwenden die Indizes 1 bis 10.
 */
int accelerations[] = {
  1000,
  6000,
  6000,
  6000,
  6000,
  6000,
  6000,
  6000,
  6000,
  6000,
  6000
};

/** @brief Alte Encoderposition zur Erkennung einer Aenderung. */
long oldPosition = -999;

/** @brief Sicherheitsweg nach der Referenzfahrt in Schritten. */
const int safeSteps = 70;

/** @brief Laenge der Fahrstrecke in Schritten. */
const int trackLength = 1750;

/**
 * @brief Texte fuer die Anzeige der Stufen.
 */
const char* stageMessages[] = {
  "Keine Stufe",
  "Stufe 1",
  "Stufe 2",
  "Stufe 3",
  "Stufe 4",
  "Stufe 5",
  "Stufe 6",
  "Stufe 7",
  "Stufe 8",
  "Stufe 9",
  "Stufe 10"
};

/**
 * @brief Allgemeine Statusmeldungen fuer das OLED-Display.
 */
const char* messages[] = {
  "Start...",
  "Startbereit",
  "Programm laeuft...",
  "Abbruch",
  ""
};

/**
 * @brief Initialisiert Hardware, Display, LEDs, Taster, Endschalter und Encoder.
 *
 * Diese Funktion wird beim Start des Arduino einmal ausgefuehrt.
 */
void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1000);

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_ENDSTOP, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));

    while (true) {
      // Programm bleibt hier stehen, falls das Display nicht gefunden wird.
    }
  }

  attachInterrupt(digitalPinToInterrupt(PIN_SW), handleInterrupt, CHANGE);

  display.display();
  delay(2000);

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  updateDisplay(messages[0], messages[4]);
  delay(1000);

  updateDisplay(messages[1], stageMessages[stage]);
  updateLEDs(false, true, false);
}

/**
 * @brief Hauptprogramm des Arduino.
 *
 * Die Funktion wird dauerhaft wiederholt.
 * Sie liest den Encoder, aktualisiert das Display und startet bei Tastendruck
 * die Referenzfahrt sowie die Demonstrationsfahrt.
 */
void loop() {
  long newPosition = encoder.read();

  if (newPosition != oldPosition) {
    stage = constrain(newPosition / 4, 1, 10);
    updateDisplay(messages[1], stageMessages[stage]);
    oldPosition = newPosition;
  }

  int buttonReading = digitalRead(PIN_BUTTON);

  if (buttonReading != lastButtonStatus) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonReading != buttonStatus) {
      buttonStatus = buttonReading;

      if (buttonStatus == LOW) {
        startProgram();
      }
    }
  }

  lastButtonStatus = buttonReading;
}

/**
 * @brief Startet den Ablauf aus Referenzfahrt und Bewegungsfahrt.
 *
 * Zuerst wird die Referenzfahrt ausgefuehrt.
 * Danach faehrt der Schlitten entsprechend der aktuell eingestellten Stufe.
 */
void startProgram() {
  stepper.setAcceleration(accelerations[0]);

  while (!findReference()) {
    stepper.setSpeed(-200);
    stepper.runSpeed();
  }

  int currentStage = stage;

  updateDisplay(messages[2], stageMessages[currentStage]);
  updateLEDs(false, false, true);

  for (int i = 0; i < 2; i++) {
    stepper.setMaxSpeed(speeds[currentStage]);
    stepper.setAcceleration(accelerations[currentStage]);

    if (i == 0) {
      stepper.move(trackLength + safeSteps);
    } else {
      stepper.move(trackLength);
    }

    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }

    stepper.move(-trackLength);

    while (stepper.distanceToGo() != 0) {
      stepper.run();
    }
  }

  updateDisplay(messages[1], stageMessages[currentStage]);
  updateLEDs(false, true, false);
}

/**
 * @brief Aktualisiert die drei Status-LEDs.
 *
 * @param red Zustand der roten LED.
 * @param green Zustand der gruenen LED.
 * @param blue Zustand der blauen LED.
 */
void updateLEDs(bool red, bool green, bool blue) {
  digitalWrite(PIN_LED_RED, red ? HIGH : LOW);
  digitalWrite(PIN_LED_GREEN, green ? HIGH : LOW);
  digitalWrite(PIN_LED_BLUE, blue ? HIGH : LOW);
}

/**
 * @brief Aktualisiert den Text auf dem OLED-Display.
 *
 * @param line1 Erste Zeile auf dem Display.
 * @param line2 Zweite Zeile auf dem Display.
 */
void updateDisplay(const char* line1, const char* line2) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.println(line1);

  if (line2[0] != '\0') {
    display.println(line2);
  }

  display.display();
}

/**
 * @brief Fuehrt die Referenzfahrt aus und prueft den Endschalter.
 *
 * Der Motor faehrt so lange in Richtung Endschalter,
 * bis der Endschalter gedrueckt wird.
 *
 * @return true, wenn der Endschalter erreicht wurde.
 * @return false, wenn der Endschalter noch nicht erreicht wurde.
 */
bool findReference() {
  int endstopReading = digitalRead(PIN_ENDSTOP);

  if (endstopReading != lastEndstopStatus) {
    lastEndstopDebounceTime = millis();
  }

  if ((millis() - lastEndstopDebounceTime) > debounceDelay) {
    if (endstopReading != endstopStatus) {
      endstopStatus = endstopReading;

      if (endstopStatus == LOW) {
        stepper.stop();
        return true;
      }
    }
  }

  lastEndstopStatus = endstopReading;
  return false;
}

/**
 * @brief Interrupt-Funktion fuer den Encoder-Taster.
 *
 * Diese Funktion wird aufgerufen, wenn sich der Zustand des Encoder-Tasters aendert.
 * Der Motor wird gestoppt und eine Abbruchmeldung wird angezeigt.
 */
void handleInterrupt() {
  stepper.stop();
  updateDisplay(messages[3], messages[4]);
  updateLEDs(true, false, false);
}