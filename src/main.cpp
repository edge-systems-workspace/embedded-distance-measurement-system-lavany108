/**
 * @file main.cpp
 * @brief Ultrasonic distance measurement example for Arduino (HC-SR04 style).
 * @author Lavanya
 * @date 2026-02-28
 *
 * @details
 * Simple example that triggers an ultrasonic sensor and measures the echo
 * pulse width to compute distance in centimetres (cm). The sketch uses
 * digital pin 9 for TRIG and digital pin 10 for ECHO. It prints readings
 * to the serial console at 9600 baud.
 *
 * Connections:
 *  - TRIG -> digital pin 9 (output, 10 µs pulse)
 *  - ECHO -> digital pin 10 (input, pulse width returned by sensor)
 *
 * Notes:
 *  - pulseIn() returns the duration of the pulse in microseconds (µs).
 *    A return value of 0 indicates a timeout / no echo detected.
 *  - Distance calculation uses speed of sound ~0.0343 cm/µs (approximate,
 *    depends on temperature and humidity).
 */

#include <Arduino.h>

/**
 * @brief Digital pin connected to the sensor TRIG (transmit) line.
 *
 * @note Use Arduino digital pin numbering. The TRIG pin is driven HIGH for a
 * 10 microsecond pulse to start the measurement. Ensure the sensor and board
 * share a common ground and that the sensor voltage levels are compatible.
 */
const int trigPin = 9;

/**
 * @brief Digital pin connected to the sensor ECHO (receive) line.
 *
 * @note ECHO is read using pulseIn(). The returned value is the width of the
 * incoming HIGH pulse in microseconds (µs).
 */
const int echoPin = 10;

/**
 * @brief Initializes I/O pins and the serial port.
 *
 * @details
 * Configures the trigger pin as an OUTPUT and the echo pin as an INPUT.
 * Initializes the serial console at 9600 baud for human-readable output of
 * measured distances.
 */
void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

/**
 * @brief Main loop: triggers the ultrasonic pulse and measures distance.
 *
 * @details
 * The measurement sequence is:
 *  1. Clear the trigger line (LOW) and wait 2 µs for stability.
 *  2. Drive TRIG HIGH for 10 µs to emit an ultrasonic burst.
 *  3. Use pulseIn(echoPin, HIGH) to time the returned echo pulse width
 *     in microseconds (µs).
 *  4. Calculate the one-way distance to the reflecting object using:
 *       distance_cm = (duration_us * 0.0343) / 2
 *     where 0.0343 cm/µs is the approximate speed of sound in air.
 *
 * Units:
 *  - duration: microseconds (µs)
 *  - distance: centimetres (cm)
 *
 * @note If pulseIn() returns 0 (timeout), no echo was detected within the
 * configured timeout. In this sketch a returned duration of 0 yields a
 * computed distance of 0 cm; applications may want to handle this case
 * specially (e.g., retry, report "out of range", or use NAN).
 *
 * @see pulseIn
 */
void loop() {

    // Clear trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send 10 microsecond pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read echo time (microseconds)
    unsigned long duration = pulseIn(echoPin, HIGH);

    // Calculate distance (cm) using speed of sound constant (0.0343 cm/µs)
    // Use float to preserve fractional centimetres and avoid narrowing.
    float distance = (static_cast<float>(duration) * 0.0343f) / 2.0f;

    Serial.print("Distance: ");
    Serial.print(distance, 2); // print with 2 decimal places
    Serial.println(" cm");

    delay(500);
}