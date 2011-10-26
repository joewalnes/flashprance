// @author Joe Walnes

#include "FlashPrance.h"

micros_t timeDifference(micros_t start, micros_t end) {
  return end - start; // TODO: Handle clock rollover
}

FlashPrance::FlashPrance(Callback* callback, int deltaThreshold)
    : _callback(callback), _deltaThreshold(deltaThreshold) {
  reset();
}

void FlashPrance::reset() {
  _lastDuration = 0;
  _lastValue = 0;
  _cycleStart = 0;
  _high = false;
  _bufferValue = 0;
  _bufferCount = 0;
}

void FlashPrance::processSignal(micros_t now, int value) {
  int delta = value - _lastValue;
  if (_high) {
    if (-delta > _deltaThreshold) {
      _lastValue = value;
      _high = false;
      flipToHigh(now);
    }
  } else {
    if (delta > _deltaThreshold) {
      _lastValue = value;
      _high = true;
      flipToLow(now);
    }
  } 
}

void FlashPrance::flipToHigh(micros_t now) {
  _callback->onSignalTransition(LOW_TO_HIGH);
  micros_t duration = timeDifference(_cycleStart, now);

  float ratio = (float)_lastDuration / (float)duration;

  // TODO: Make these hardcoded values configurable
  if (ratio < 0.3) {
    processBit(now, TOO_SHORT);
  } else if (ratio < 0.68) {
    processBit(now, ZERO);
  } else if (ratio < 0.72) {
    processBit(now, NEUTRAL);
  } else if (ratio < 1.0) {
    processBit(now, ONE);
  } else {
    processBit(now, TOO_LONG);
  }

  _cycleStart = now;
}

void FlashPrance::flipToLow(micros_t now) {
  _callback->onSignalTransition(HIGH_TO_LOW);
  _lastDuration = timeDifference(_cycleStart, now);
}

void FlashPrance::processBit(micros_t now, BitType bitType) {
  _callback->onDecodeBit(bitType);
  switch (bitType) {
    case TOO_SHORT:
    case TOO_LONG:
    case NEUTRAL:
      _bufferValue = 0;
      _bufferCount = 0;
      break;
    case ZERO:
      _bufferCount++;
      _bufferValue <<= 1;
      break;
    case ONE:
      _bufferCount++;
      _bufferValue <<= 1;
      _bufferValue++;
      break;
  default:
      break;
  }
  if (_bufferCount == 8) {
    processByte(now, (int)_bufferValue);
    _bufferValue = 0;
    _bufferCount = 0;
  }
}

void FlashPrance::processByte(micros_t now, int value) {
  _callback->onByte(value);
}

