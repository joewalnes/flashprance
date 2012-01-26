// TODO: Packet boundaries
// TODO: Checksum

function FlashPrance() {
}

FlashPrance.prototype.transmitAscii = function(str) {
  FlashPrance.debugMsg('transmit ascii:', str);
  this.transmitBits(this.asciiToBits(str));
}

FlashPrance.prototype.transmitBits = function(bits) {
  if (this.transmitting) {
    throw 'Cannot transmit until previous transmission has ended.';
  }
  FlashPrance.debugMsg('raw bits:', bits);
  FlashPrance.debugMsg('should take:', bits.length * Math.round(1000 / this.fps) + 'ms');
  var index = 0;
  var self = this;
  var start = new Date().getTime();
  self.transmitting = true;
  var interval = setInterval(function() {
    if (!self.transmitting) {
      clearInterval(interval);
      return;
    }
    if (index == 0) {
      self.ontransmitstart();
      self.ontransmitprogress(0);
    }
    if (index == bits.length) {
      FlashPrance.debugMsg('completed in:',
                       (new Date().getTime() - start) + 'ms');
      clearInterval(interval);
      self.ontransmitvalue(0, 0); // ensure emitter is left in off state
      self.ontransmitprogress(1);
      self.ontransmitend();
      self.transmitting = false;
    } else {
      self.ontransmitvalue(index % 2, bits[index++]);
      if (index % self.progressReportInterval == 0) {
        self.ontransmitprogress(index / bits.length);
      }
    }
  }, 1000 / this.fps);
};

/**
 * Abort current transmission (if still in progress).
 */
FlashPrance.prototype.abortTransmission = function() {
  if (this.transmitting) {
    FlashPrance.debugMsg('aborting transmission');
    this.transmitting = false;
    this.ontransmitvalue(0, 0); // ensure emitter is left in off state
    this.ontransmitend();
  } else {
    FlashPrance.debugMsg('no transmission to abort');
  }
};

/**
 * Extract bits from ASCII string.
 */
FlashPrance.prototype.asciiToBits = function(str) {
  var bits = [];
  for (var i = 0; i < str.length; i++) {
    var b = str[i].charCodeAt();
    for (var j = 7; j >= 0; j--) {
      bits.push((b >> j) & 1);
    }
  }
  return bits;
};

FlashPrance.debug = false;
FlashPrance.prototype.fps = 60;
FlashPrance.prototype.progressReportInterval = 1;
FlashPrance.prototype.transmitting = false;
FlashPrance.prototype.ontransmitstart    = function() {};
FlashPrance.prototype.ontransmitend      = function() {};
FlashPrance.prototype.ontransmitvalue    = function(dark) {};
FlashPrance.prototype.ontransmitprogress = function(progress) {};

FlashPrance.debugMsg = function() {
  if (FlashPrance.debug && console && console.log) {
    console.log.apply(console, arguments);
  }
};
