/**
 * Really simple Arduino demo of FlashPrance.
 *
 * To use:
 *
 * - Connect a light sensor to port Analog 0
 *   of Arduino.
 *   Recommend: http://www.sparkfun.com/products/8688
 *
 * - Build and upload this sketch to Arduino.
 *
 * - Open serial port monitor.
 *
 * - Goto http://flashprance.appspot.com/, type some
 *   data in, hold up light sensor to box on screen and
 *   hit transmit.
 *
 * - You should see the data echo'd (slowly) over the
 *   Arduino serial port. 
 */

#include <FlashPrance.h>

const int lightSensorPin = 0;
const int ledHighPin = 13;

const micros_t microsBetweenSamples = 100;
micros_t lastSample = 0;

class : public FlashPrance::Callback {
  
  /** FlashPrance callback: echo's byte to serial port. */
  virtual void onByte(int b) {
    Serial.print((char)b);
  }
  
  /** Optional FlashPrance callback to aid debugging - turns
   *  LED on/off based on whether a flash is being seen. */
  virtual void onSignalTransition(FlashPrance::Transition transition) {
    digitalWrite(ledHighPin, transition == FlashPrance::LOW_TO_HIGH ? HIGH : LOW);
  }

} handler;

FlashPrance flashPrance(&handler, 100);

void setup() {
  pinMode(ledHighPin, OUTPUT);  
  Serial.begin(9600);
  Serial.println("Awaiting data...");
}

void loop() {
  micros_t now = micros();

  if (timeDifference(lastSample, now) >= microsBetweenSamples) {   
    lastSample = now;
    int value = (analogRead(lightSensorPin) >> 2);
    flashPrance.processSignal(now, value);
  }
}
