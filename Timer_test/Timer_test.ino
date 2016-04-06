void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  OCR1A = 100;
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler
  //interrupts();
 
}
  
  //interrupts();
void loop() {
  // put your main code here, to run repeatedly:

}
