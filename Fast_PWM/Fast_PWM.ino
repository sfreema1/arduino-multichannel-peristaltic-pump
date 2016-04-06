void setup() {
  //Fast PWM mode
pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  //TCCR2a- Timer 2 Channel A Timer Counter Control Register A 
  //COM2A + COM2B set to 10 - provides non-inverted PWM
  // 011 for WGM sets to Fast PWM
  //CS to 100 sets prescalar to 64
  TCCR2B = _BV(CS22);
  //Set CS To 100 sets divides clcok by 64
  OCR2A = 180;
  OCR2B = 50;
  //Output Control Register control PWM duty cycle

}

void loop() {
  // put your main code here, to run repeatedly:

}
