/**
 * @file CNCShieldAxisDemo.ino
 * @brief Simple project-related axis movement for the CNC hot wire foam cutter.
 
 * @date 2026-05-25
 */

const uint8_t ENABLE_PIN = 8; /**< Enable pin for all stepper drivers, active LOW. */

const uint8_t X_STEP_PIN = 2; /**< STEP pin for the X-axis driver. */
const uint8_t X_DIR_PIN  = 5; /**< DIR pin for the X-axis driver. */
const uint8_t Y_STEP_PIN = 3; /**< STEP pin for the Y-axis driver. */
const uint8_t Y_DIR_PIN  = 6; /**< DIR pin for the Y-axis driver. */

const unsigned long TRAVEL_STEPS = 1200;        /**< Number of steps for one travel movement. */
const unsigned int CUTTING_DELAY_US = 1600;     /**< Slow feed movement delay. */
const unsigned int RETURN_DELAY_US  = 750;      /**< Faster return movement delay. */

/**
 * @brief Moves the X- and Y-axis together.
 *
 * @param steps Number of step pulses.
 * @param delayUs Delay between HIGH and LOW level in microseconds.
 */
void moveXY(unsigned long steps, unsigned int delayUs)
{
    for (unsigned long i = 0; i < steps; i++)
    {
        digitalWrite(X_STEP_PIN, HIGH);
        digitalWrite(Y_STEP_PIN, HIGH);
        delayMicroseconds(delayUs);

        digitalWrite(X_STEP_PIN, LOW);
        digitalWrite(Y_STEP_PIN, LOW);
        delayMicroseconds(delayUs);
    }
}

/**
 * @brief Initializes the CNC Shield pins.
 */
void setup()
{
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);

    digitalWrite(ENABLE_PIN, LOW);
}

/**
 * @brief Simulates a simple cutting movement and return movement.
 */
void loop()
{
    digitalWrite(X_DIR_PIN, HIGH);
    digitalWrite(Y_DIR_PIN, HIGH);
    moveXY(TRAVEL_STEPS, CUTTING_DELAY_US);
    delay(1500);

    digitalWrite(X_DIR_PIN, LOW);
    digitalWrite(Y_DIR_PIN, LOW);
    moveXY(TRAVEL_STEPS, RETURN_DELAY_US);
    delay(1500);
}
