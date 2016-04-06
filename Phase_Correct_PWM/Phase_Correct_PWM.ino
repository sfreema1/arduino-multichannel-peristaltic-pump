void setup(){
  //Are OCRA2A and OCRA2B sending out completely different signals?

  //Output A frequency: 16 MHz / 64 / 256 = 976.5625Hz
  //Output A duty cycle: (180+1) / 256 = 70.7%
  //Output B frequency: 16 MHz / 64 / 256 = 976.5625Hz
  //Output B duty cycle: (50+1) / 256 = 19.9%



  //Phase Correct PWM- All in Timer 1 - 2 seperate waves
  //How do we change the frequency? - chnage the prescalar- look at CS bits
  //CS10 - set to 0 bit, CS 11- set to 1 bit, CS 12- set to 2 bits
  //prescalar = 1 - 16 Mhz, 001, prescalar = 8- 2 Mhz, 010,
  //Divide 16Mhz by prescalar then 256 then off by 2
  //prescalar = 64
  //How to choose the frequency? - Next assignment
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(CS12);
  OCR1A = 180;
  OCR1B = 50;

  //interrupts();
  //Output A frequency: 16 MHz / 64 / 255 / 2 = 490.196Hz
  //Output A duty cycle: 180 / 255 = 70.6%
  //Output B frequency: 16 MHz / 64 / 255 / 2 = 490.196Hz
  //Output B duty cycle: 50 / 255 = 19.6%
}

void loop() {
  // put your main code here, to run repeatedly:


}
