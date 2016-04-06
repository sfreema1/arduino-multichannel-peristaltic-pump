void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // CTC Mode - Top is OCR1A
  // Mode WGM13 = 0 | WGM12 = 1 | WGM11 = 0 | WGM10 = 0
  // COM1A1/COM1B1 = 0
  // COM1A0/COM1B0 = 1
  // 256 Presccaler = CS12 ON TCCR1B = 1
  TCCR1A = B01010000;
  TCCR1B = B00001100;
  OCR1A = 180;
  TCNT1 = 0;
}

void loop() {

}

