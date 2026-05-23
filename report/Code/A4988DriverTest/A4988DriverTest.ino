/**
 * @file A4988DriverTest.ino
 * @brief Test program for the A4988 stepper motor driver.

 */

const uint8_t STEP_PIN = 2;
const uint8_t DIR_PIN  = 5;
const uint8_t EN_PIN   = 8;

const unsigned int STEPS_PER_TEST = 400;

/**
 * @brief Generates a defined number of step pulses.
 *
 * @param steps Number of step pulses.
 * @param delayUs Delay between HIGH and LOW level in microseconds.
 */
void moveSteps(unsigned int steps, unsigned int delayUs)
{
    for (unsigned int i = 0; i < steps; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delayUs);

        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delayUs);
    }
}

/**
 * @brief Initializes the output pins.
 */
void setup()
{
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW);
}

/**
 * @brief Executes a complete driver function test.
 */
void loop()
{
    digitalWrite(DIR_PIN, HIGH);
    moveSteps(STEPS_PER_TEST, 1200);

    delay(1000);

    digitalWrite(DIR_PIN, LOW);
    moveSteps(STEPS_PER_TEST, 1200);

    delay(1000);

    digitalWrite(DIR_PIN, HIGH);
    moveSteps(STEPS_PER_TEST, 600);

    delay(1000);

    digitalWrite(EN_PIN, HIGH);

    delay(2000);

    digitalWrite(EN_PIN, LOW);

    delay(1000);
}