/**
 * @file druckknoepfeledabfolge.ino
 * @brief Steuert eine LED-Abfolge mit drei Druckknoepfen.
 *
 * Mit dem Start-Druckknopf wird die LED-Abfolge gestartet.
 * Mit dem Pause-Druckknopf wird die Abfolge pausiert oder fortgesetzt.
 * Mit dem Stop-Druckknopf wird die Abfolge beendet und alle LEDs werden ausgeschaltet.
 */

const int startdruckknopf = 2;  ///< Eingangspin fuer den Start-Druckknopf
const int pausedruckknopf = 3;  ///< Eingangspin fuer den Pause-Druckknopf
const int stopdruckknopf  = 4;  ///< Eingangspin fuer den Stop-Druckknopf

const int ledPins[] = {8, 9, 10, 11, 12}; ///< Ausgangspins fuer die LEDs
const int anzahlLeds = 5;                 ///< Anzahl der angeschlossenen LEDs

bool programmLaeuft = false; ///< Gibt an, ob die LED-Abfolge aktiv ist
bool programmPause = false;  ///< Gibt an, ob die LED-Abfolge pausiert ist

int aktuelleLed = 0;                 ///< Nummer der aktuell eingeschalteten LED
unsigned long letzteZeit = 0;        ///< Zeitpunkt der letzten LED-Umschaltung
const unsigned long intervall = 500; ///< Zeitabstand zwischen den LEDs in Millisekunden

bool letzterPauseStatus = HIGH; ///< Vorheriger Zustand des Pause-Druckknopfs

/**
 * @brief Wird einmal beim Start des Arduino ausgefuehrt.
 *
 * Die Druckknoepfe werden als Eingange mit internem Pull-up-Widerstand festgelegt.
 * Die LED-Pins werden als Ausgaenge festgelegt.
 */
void setup() {
  pinMode(startdruckknopf, INPUT_PULLUP); ///< Start-Druckknopf als Eingang
  pinMode(pausedruckknopf, INPUT_PULLUP); ///< Pause-Druckknopf als Eingang
  pinMode(stopdruckknopf, INPUT_PULLUP);  ///< Stop-Druckknopf als Eingang

  for (int i = 0; i < anzahlLeds; i++) {
    pinMode(ledPins[i], OUTPUT); ///< LED-Pin als Ausgang festlegen
  }

  alleLedsAus();
}

/**
 * @brief Hauptprogramm, das dauerhaft wiederholt wird.
 *
 * Es prueft die drei Druckknoepfe und steuert je nach Eingabe
 * den Ablauf der LEDs.
 */
void loop() {
  if (digitalRead(startdruckknopf) == LOW) {
    programmLaeuft = true;
    programmPause = false;
  }

  if (digitalRead(stopdruckknopf) == LOW) {
    programmLaeuft = false;
    programmPause = false;
    aktuelleLed = 0;
    alleLedsAus();
  }

  bool aktuellerPauseStatus = digitalRead(pausedruckknopf); ///< Aktueller Zustand des Pause-Druckknopfs

  if (letzterPauseStatus == HIGH && aktuellerPauseStatus == LOW) {
    programmPause = !programmPause;
    delay(200); ///< Einfache Entprellung des Druckknopfs
  }

  letzterPauseStatus = aktuellerPauseStatus;

  if (programmLaeuft && !programmPause) {
    ledAbfolge();
  }
}

/**
 * @brief Schaltet alle LEDs aus.
 *
 * Alle LED-Pins werden auf LOW gesetzt.
 */
void alleLedsAus() {
  for (int i = 0; i < anzahlLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

/**
 * @brief Laesst die LEDs nacheinander aufleuchten.
 *
 * Nach Ablauf des festgelegten Intervalls wird die aktuelle LED ausgeschaltet
 * und die naechste LED eingeschaltet.
 */
void ledAbfolge() {
  unsigned long aktuelleZeit = millis(); ///< Aktuelle Laufzeit des Arduino in Millisekunden

  if (aktuelleZeit - letzteZeit >= intervall) {
    letzteZeit = aktuelleZeit;

    alleLedsAus();
    digitalWrite(ledPins[aktuelleLed], HIGH);

    aktuelleLed++;

    if (aktuelleLed >= anzahlLeds) {
      aktuelleLed = 0;
    }
  }
}