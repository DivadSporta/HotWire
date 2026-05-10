/**
 * @file druckknopfrtest.ino
 * @brief Testet einen Druckknopf und gibt 0 oder 1 im seriellen Monitor aus.
 *
 * Der Druckknopf ist zwischen Pin 2 und GND angeschlossen.
 * Es wird der interne Pull-up-Widerstand verwendet.
 */

const int druckknopfPin = 2; ///< Pin, an dem der Druckknopf angeschlossen ist

/**
 * @brief Wird einmal beim Start des Arduino ausgefuehrt.
 *
 * Der Druckknopf-Pin wird als Eingang mit internem Pull-up-Widerstand festgelegt.
 * Die serielle Ausgabe wird gestartet.
 */
void setup() {
  pinMode(druckknopfPin, INPUT_PULLUP); ///< Eingang mit internem Pull-up
  Serial.begin(115200);               ///< Startet die serielle Verbindung
}

/**
 * @brief Hauptprogramm, das dauerhaft wiederholt wird.
 *
 * Gibt 1 aus, wenn der Druckknopf gedrueckt ist.
 * Gibt 0 aus, wenn der Druckknopf nicht gedrueckt ist.
 */
void loop() {
  int druckknopfStatus = digitalRead(druckknopfPin); ///< Liest den Zustand des Druckknopf

  if (druckknopfStatus == LOW) {
    Serial.println(1); ///< Druckknopf gedrueckt
  } else {
    Serial.println(0); ///< Druckknopf nicht gedrueckt
  }

  delay(200); ///< Kurze Pause fuer eine lesbare Ausgabe
}