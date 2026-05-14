\begin{lstlisting}[language=C++]
/**
 * @file TestButton.ino
 * @brief Tests a push button connected to digital pin D2.
 *
 * The button is connected between digital pin D2 and GND.
 * The internal pull-up resistor is enabled with INPUT_PULLUP.
 * Therefore, the input reads HIGH when the button is not pressed
 * and LOW when the button is pressed.
 */

const int buttonPin = 2;  ///< Digital input pin connected to the button.

/**
 * @brief Initializes serial communication and configures the button pin.
 */
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

/**
 * @brief Reads the button state and prints it to the serial monitor.
 */
void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    Serial.println("Button pressed");
  } else {
    Serial.println("Button not pressed");
  }

  delay(200);
}
\end{lstlisting}