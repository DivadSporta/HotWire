/**
 * @file SPIGrundtest.ino
 * @brief Basic SPI communication test for the Arduino Uno.
 *
 * The Arduino Uno uses D10 as CS/SS, D11 as MOSI,
 * D12 as MISO and D13 as SCK.
 */

#include <SPI.h>

const int chipSelectPin = 10; ///< Digital output pin used as chip select.

/**
 * @brief Initializes SPI and configures the chip select pin.
 */
void setup()
{
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);

  SPI.begin();

  Serial.begin(115200);
  Serial.println("SPI Grundtest gestartet");
}

/**
 * @brief Sends one byte over SPI repeatedly.
 */
void loop()
{
  byte sendData = 0x55;

  digitalWrite(chipSelectPin, LOW);
  byte receivedData = SPI.transfer(sendData);
  digitalWrite(chipSelectPin, HIGH);

  Serial.print("Gesendet: ");
  Serial.print(sendData, HEX);
  Serial.print(" Empfangen: ");
  Serial.println(receivedData, HEX);

  delay(1000);
}