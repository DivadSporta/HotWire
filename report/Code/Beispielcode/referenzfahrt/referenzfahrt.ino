/**
 * @file referenzfahrt.ino
 * @brief Homing routine using a stepper motor, A4988 driver, and endstop.
 */

/** @brief STEP pin of the driver */
const int stepPin = 2;

/** @brief Direction pin of the driver */
const int dirPin = 5;

/** @brief Enable pin of the driver */
const int enPin = 8;

/** @brief Endstop input pin */
const int endstopPin = 9;

/** @brief Step delay in microseconds */
const int stepDelayUs = 1000;

/** @brief Number of steps for the backoff movement */
const int backoffSteps = 50;

/** @brief Initializes the hardware and starts the homing routine */
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

/** @brief Main loop (unused in this example) */
void loop() {
}

/** @brief Executes a single motor step */
void oneStep() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelayUs);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelayUs);
}

/**
 * @brief Moves the motor by a defined number of steps
 * @param steps Number of steps to execute
 * @param dir Direction of movement (LOW/HIGH)
 */
void moveSteps(int steps, bool dir) {
  digitalWrite(dirPin, dir);
  for (int i = 0; i < steps; i++) {
    oneStep();
  }
}

/** @brief Performs the homing sequence and backoff movement */
void homeAxis() {
  while (digitalRead(endstopPin) == HIGH) {
    oneStep();
  }

  delay(200);
  moveSteps(backoffSteps, HIGH);
}