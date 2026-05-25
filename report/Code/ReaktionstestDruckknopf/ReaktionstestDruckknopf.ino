/**
 * @file ReaktionstestDruckknopf.ino
 * @brief Simple reaction test using an LED and a push button.
 */

/** @brief Digital input pin for the push button. */
const int druckknopfPin = 2;

/** @brief Digital output pin for the LED. */
const int ledPin = 13;

/** @brief Stores the state of the push button. */
int druckknopfZustand = HIGH;

/**
 * @brief Initializes the pins and the serial monitor.
 */
void setup()
{
    pinMode(druckknopfPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    digitalWrite(ledPin, LOW);

    randomSeed(analogRead(A0));

    Serial.println("Reaktionstest gestartet");
    Serial.println("Druecke den Druckknopf, sobald die LED leuchtet.");
}

/**
 * @brief Runs the reaction test repeatedly.
 */
void loop()
{
    Serial.println("Warten...");
    digitalWrite(ledPin, LOW);

    delay(random(2000, 6000));

    Serial.println("Jetzt druecken!");
    digitalWrite(ledPin, HIGH);

    while (digitalRead(druckknopfPin) == HIGH)
    {
        // Warten, bis der Druckknopf gedrueckt wird.
    }

    digitalWrite(ledPin, LOW);

    Serial.println("Druckknopf wurde gedrueckt.");
    Serial.println("Naechster Durchlauf startet gleich.");
    Serial.println();

    delay(2000);
}