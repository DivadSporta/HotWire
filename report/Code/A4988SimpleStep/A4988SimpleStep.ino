/**
 * @file A4988SimpleStep.ino
 * @brief Basic function test for an A4988 stepper motor driver.

 */

const uint8_t STEP_PIN = 2;
const uint8_t DIR_PIN  = 5;
const uint8_t EN_PIN   = 8;

const unsigned int STEP_DELAY_US = 1000;

/**
 * @brief Initializes the output pins and enables the driver.
 */
void setup()
{
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(EN_PIN, LOW);
}

/**
 * @brief Generates continuous step pulses.
 */
void loop()
{
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY_US);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY_US);
}