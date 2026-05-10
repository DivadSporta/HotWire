/**
 * @file ledmitdruckknopf.ino
 * @brief Schaltet eine LED ein, solange ein Druckknopf gedrueckt wird.
 *
 * Der Druckknopf ist zwischen Pin 2 und GND angeschlossen.
 * Die LED ist mit einem 220 Ohm oder 330 Ohm Vorwiderstand an Pin 13 angeschlossen.
 * Der lange LED-Anschluss ist die Anode (+), der kurze Anschluss ist die Kathode (-).
 */

const int druckknopfPin = 2;   ///< Pin, an dem der Druckknopf angeschlossen ist
const int ledPin = 13;     ///< Pin, an dem die LED angeschlossen ist

/**
 * @brief Wird einmal beim Start des Arduino ausgefuehrt.
 *
 * Hier werden die Pins als Ein- oder Ausgang festgelegt.
 */
void setup() {
  pinMode(druckknopfPin, INPUT_PULLUP); ///< Druckknopfeingang mit internem Pull-up
  pinMode(ledPin, OUTPUT);          ///< LED-Pin als Ausgang
}

/**
 * @brief Hauptprogramm, das dauerhaft wiederholt wird.
 *
 * Wenn der Druckknopf gedrueckt wird, wird die LED eingeschaltet.
 * Wird der Druckknopf losgelassen, wird die LED ausgeschaltet.
 */
void loop() {
  int druckknopfStatus = digitalRead(druckknopfPin); ///< Aktueller Zustand des Druckknopfes

  if (druckknopfStatus == LOW) {
    digitalWrite(ledPin, HIGH); ///< LED einschalten
  } else {
    digitalWrite(ledPin, LOW);  ///< LED ausschalten
  }
}