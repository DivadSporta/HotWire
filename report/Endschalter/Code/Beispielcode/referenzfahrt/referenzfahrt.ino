/**
 * @file referenzfahrt.ino
 * @brief Referenzfahrt mit Schrittmotor, A4988 und Endschalter.
 */

/** @brief STEP-Pin des Treibers */
const int stepPin = 2;

/** @brief Richtungs-Pin des Treibers */
const int dirPin = 5;

/** @brief Enable-Pin des Treibers */
const int enPin = 8;

/** @brief Endschalter-Pin */
const int endstopPin = 9;

/** @brief Schrittverzoegerung in Mikrosekunden */
const int stepDelayUs = 1000;

/** @brief Schritte fuer Rueckfahrt */
const int backoffSteps = 50;

/** @brief Initialisierung und Start der Referenzfahrt */
void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(endstopPin, INPUT_PULLUP);

  Serial.begin(115200);

  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, LOW);

  homeAxis();
}

/** @brief Hauptschleife (leer) */
void loop() {
}

/** @brief Fuehrt einen einzelnen Schritt aus */
void oneStep() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelayUs);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelayUs);
}

/**
 * @brief Bewegt Motor um Anzahl Schritte
 * @param steps Anzahl Schritte
 * @param dir Richtung (LOW/HIGH)
 */
void moveSteps(int steps, bool dir) {
  digitalWrite(dirPin, dir);
  for (int i = 0; i < steps; i++) {
    oneStep();
  }
}

/** @brief Referenzfahrt bis Endschalter + Rueckfahrt */
void homeAxis() {
  while (digitalRead(endstopPin) == HIGH) {
    oneStep();
  }

  delay(200);
  moveSteps(backoffSteps, HIGH);
}