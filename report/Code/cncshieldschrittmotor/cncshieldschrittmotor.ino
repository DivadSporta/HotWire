/**
 * @file cncshieldschrittmotor.ino
 * @brief Moves a stepper motor with the CNC Shield V3.
 *
 * The stepper motor is connected to the X-axis driver of the CNC Shield V3.
 * The motor moves continuously in one direction.
 */

const int stepPin = 2;   ///< STEP pin for the X-axis driver.
const int dirPin = 5;    ///< DIR pin for the X-axis driver.
const int enablePin = 8; ///< Enable pin for the stepper drivers.

const int stepDelay = 1000; ///< Delay between steps in microseconds.

/**
 * @brief Runs once when the Arduino starts.
 *
 * The STEP, DIR, and ENABLE pins are configured as outputs.
 */
void setup() {
  pinMode(stepPin, OUTPUT);   ///< Sets the STEP pin as output.
  pinMode(dirPin, OUTPUT);    ///< Sets the DIR pin as output.
  pinMode(enablePin, OUTPUT); ///< Sets the ENABLE pin as output.

  digitalWrite(enablePin, LOW); ///< Enables the stepper driver.
  digitalWrite(dirPin, HIGH);   ///< Sets the movement direction.
}

/**
 * @brief Main program that runs repeatedly.
 *
 * One step pulse is created again and again.
 * This makes the stepper motor rotate continuously.
 */
void loop() {
  digitalWrite(stepPin, HIGH); ///< Starts one step pulse.
  delayMicroseconds(stepDelay);

  digitalWrite(stepPin, LOW); ///< Ends one step pulse.
  delayMicroseconds(stepDelay);
}