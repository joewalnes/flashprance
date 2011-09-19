FlashPrance
===========

FlashPrance is a toolkit allowing data to be transferred by flashing
lights on and off.


Application
-----------

It's primary purpose is to allow settings to be sent from a computer or
cellphone to an embedded device, such as an Arduino.

The screen of the computer or cellphone will quickly flash between black
and white at different intervals, and the device shall measure the
duration of the light intervals to decode the data.

Because bandwidth is limited by the frames per second that can be
displayed on screen, it is only suitable for very small amounts of data.
It takes roughly 1 second to transfer 1 byte.

It's benefit is the cost and convenience. The sender (computer or
cellphone) does not need any additional hardware or drivers - only the
capability to flash an area of the screen - this may even be a web page.
The only additional components on the receiver (embedded circuite) are a
light sensor and a resistor - this should cost less than $1. 


Planned Features
----------------

*This is still an early work in progress - most of these features are
not implemented yet.*

Sender implementation libraries:

*   Web: JavaScript (DONE)
*   iOS: Objective-C (TODO)
*   Android: Java (TODO)
*   Terminal console: NCurses/ANSI (TODO)
*   Generic C++: algorithm + {MFC,GTK,QT,WinForms,...} (TODO)
*   Generic Java: algorithm + {Swing,SWT} (TODO)

Receiver implementation libraries:

*   Arduino (DONE)
*   Generic C: {atmega,attiny,msp430,arm,pic,...} (TODO)

Communication protocol:

*   Data streaming (DONE)
*   Clock syncronization (DONE)
*   Manchester encoding (TODO)
*   8B/10B encoding (TODO)
*   Message framing: start/length/end (TODO)
*   Checksums (TODO)


