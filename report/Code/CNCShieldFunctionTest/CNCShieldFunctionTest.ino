/**
 * @file CNCShieldFunctionTest.ino
 * @brief Function test for the CNC Shield V3.
 
 * @date 2026-05-23
 */

const uint8_t STEP_PIN = 2;
const uint8_t DIR_PIN  = 5;
const uint8_t EN_PIN   = 8;

const unsigned int STEPS = 300;

/**
 * @brief Moves the motor for a defined number of steps.
 *
 * @param delayUs Delay between step edges in microseconds.
 */
void moveMotor(unsigned int delayUs)
{
    for (unsigned int i = 0; i < STEPS; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delayUs);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delayUs);
    }
}

/**
 * @brief Initializes the CNC Shield control pins.
 */
void setup()
{
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW);
}

/**
 * @brief Repeats the complete function test.
 */
void loop()
{
    digitalWrite(DIR_PIN, HIGH);
    moveMotor(1200);
    delay(1000);

    digitalWrite(DIR_PIN, LOW);
    moveMotor(1200);
    delay(1000);

    digitalWrite(DIR_PIN, HIGH);
    moveMotor(600);
    delay(1000);

    digitalWrite(EN_PIN, HIGH);
    delay(1500);

    digitalWrite(EN_PIN, LOW);
    delay(1000);
}