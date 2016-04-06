https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
-Explains PWM really well and what pins work/ how timers work


http://www.fiz-ix.com/2012/01/how-to-configure-arduino-timer-2-registers-to-drive-an-ultrasonic-transducer-with-a-square-wave/
-Example and explanation of working code

http://web.csulb.edu/~hill/ee470/Lab%202d%20-%20Sine_Wave_Generator.pdf
-Sine Wave Generator


https://www.arduino.cc/en/Tutorial/DueSimpleWaveformGenerator
-Make all different types of waves

http://www.atmel.com/images/atmel-8393-mcu_wireless-atmega256rfr2-atmega128rfr2-atmega64rfr2_datasheet.pdf
-ATMEL microprocessor - “register summary”


http://playground.arduino.cc/Code/Timer1
-Possibly one way to create new period setPeriod(period)

-Ways to control frequency
-setPeriod(period)?
-Possibly might work
-Varying top timer limit
	-OCRA as top limit
http://playground.arduino.cc/Main/TimerPWMCheatsheet
-Another way to change frequency
-millis(),micros(),delay()

http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/
-Timer 1 works with Servo Library
-Timer 0 works with delay() and millis()
-Has all the registers displayed

timer 0 (controls pin 13, 4)
timer 1 (controls pin 12, 11)
timer 2 (controls pin 10, 9)
timer 3 (controls pin 5, 3, 2)
timer 4 (controls pin 8, 7, 6)

https://www.arduino.cc/en/Reference/AttachInterrupt
-Only certain digital pin interrupts available
	-for mega it is 2,3,18,20,21
-IRS- Interrupt Service Routine, no parameters and cannot return anything
-short and fast as possible, only one at a time
-*if needed only micros() would work*
-volatile - allows you to share between ISR and main program


attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
Recommended way to implement
pin#
ISR routine to call when interrupt occurs
Mode
 LOW - to trigger interrupt when pin is LOW
CHANGE- to trigger interrupt when pin CHANGES value
RISING- trigger when pin goes low to high
FALLING- trigger when pin goes from low to high
-We could possibly write a code to set a user-defined interval then set the pin to low or change when that variable is hit then wait however long
http://playground.arduino.cc/Code/Interrupts
-pin change interrupts can be enabled on many pins with Arduino- almost all of MEga
	-Code to look over for interrupt and timer
	https://gonium.net/md/2007/04/18/tweaking-the-code/

https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
-Could set up a comparison register for Timer 0 - OCROA to generate interrupt in middle of count


http://letsmakerobots.com/node/28278
-Goes over all the basic and starts to delve into timers and timer interrupts
-Timer overflow- timer has reached its limit value
- has some really great examples and walkthroughs

https://www.arduino.cc/en/Reference/DetachInterrupt
-detach interrupt- turns off given interrupt

detachInterrupt(interrupt)
detachInterrupt(digitalPinToInterrupt(pin));
Interrupt- # of interrupts to disable
Pin- pin # of interrupt to disable



