#pragma once

typedef unsigned long micros_t;

micros_t timeDifference(micros_t start, micros_t end);

/**
 * FlashPrance: Reads an analog light sensor value, and looks
 * for flashing patterns sent form a FlashPrance writer, and
 * decodes the binary data.
 *
 * Basic usage:
 *
 *
 * 1. Create a callback handler class
 *
 * This will receive callbacks when bytes are received.
 *
 *   class : public FlashPrance::Callback {
 *     virtual void onByte(int b) {
 *       Serial.print(b); // or whatever you want to do
 *     }
 *   } myHandler;
 *
 *
 * 2. Create a FlashPrance instance, passing it the handler
 *
 *   FlashPrance flashPrance(&handler);
 *
 *
 * 3. Send analog signal to FlashPrance
 *
 *   // Repeat this every 100 microseconds via a loop
 *   // or interrupt
 *   unsigned long currentTime = // current timestamp in micros
 *   int light = analogRead(...); // read light level
 *   flashPrance.processSignal(currentTime, lightLevel);
 *
 * The FlashPrance.processSignal() will buffer up the values
 * and call onByte() whenever it detects a complete byte.
 *
 *
 * @author Joe Walnes
 */
class FlashPrance {

public:

  enum Transition { HIGH_TO_LOW, LOW_TO_HIGH };
  enum BitType { ZERO, ONE, TOO_SHORT, NEUTRAL, TOO_LONG };

  /**
   *
   */
  class Callback {
  public:
    virtual void onByte(int b) = 0;

    virtual void onSignalTransition(Transition transition) {}
    virtual void onDecodeBit(BitType bitType) {}
  };

  FlashPrance(Callback* callback, int deltaThreshold = 1);

  virtual void reset();
  virtual void processSignal(micros_t now, int value);

private:

  virtual void flipToHigh(micros_t now);
  virtual void flipToLow(micros_t now);
  virtual void processBit(micros_t now, BitType bitType);
  virtual void processByte(micros_t now, int value);

  Callback* _callback;

  const int _deltaThreshold;
  int _lastValue;
  bool _high;

  micros_t _lastDuration;
  micros_t _cycleStart;

  char _bufferValue;
  int _bufferCount;

};

