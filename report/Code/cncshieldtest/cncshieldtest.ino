/**
 * @file cncshieldtest.ino
 * @brief Tests the CNC Shield V3 with a stepper motor on the X-axis.
 *
 * The motor driver is enabled through the ENABLE pin.
 * The motor moves first in one direction and then in the other direction.
 * This checks whether the shield, driver, and motor connection work correctly.
 */

const int stepPin = 2;   ///< STEP pin for the X-axis driver.
const int dirPin = 5;    ///< DIR pin for the X-axis driver.
const int enablePin = 8; ///< Enable pin for the stepper drivers.

const int stepDelay = 1000;     ///< Delay between steps in microseconds.
const int stepsPerMove = 400;   ///< Number of steps for one movement direction.
const int pauseTime = 1000;     ///< Pause between direction changes in milliseconds.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The STEP, DIR, and ENABLE pins are configured as outputs.
 * The stepper driver is enabled.
 */
void setup() {
  pinMode(stepPin, OUTPUT);   ///< Sets the STEP pin as output.
  pinMode(dirPin, OUTPUT);    ///< Sets the DIR pin as output.
  pinMode(enablePin, OUTPUT); ///< Sets the ENABLE pin as output.

  digitalWrite(enablePin, LOW); ///< Enables the stepper driver.
}

/**
 * @brief Main program that runs repeatedly.
 *
 * The motor moves a defined number of steps in one direction.
 * After a short pause, the direction is changed and the motor moves back.
 */
void loop() {
  digitalWrite(dirPin, HIGH); ///< Sets the first movement direction.
  moveSteps(stepsPerMove);

  delay(pauseTime); ///< Waits before changing direction.

  digitalWrite(dirPin, LOW); ///< Sets the opposite movement direction.
  moveSteps(stepsPerMove);

  delay(pauseTime); ///< Waits before starting the next cycle.
}

/**
 * @brief Moves the stepper motor by a defined number of steps.
 *
 * A step pulse is created for each step.
 *
 * @param steps Number of steps the motor should move.
 */
void moveSteps(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH); ///< Starts one step pulse.
    delayMicroseconds(stepDelay);

    digitalWrite(stepPin, LOW); ///< Ends one step pulse.
    delayMicroseconds(stepDelay);
  }
}