//noInterrupts();

//cli() - clear the i bit, stops all interrupts

//interrupts()/sei()- turn interrupts back on

//CTC mode- Clear Timer on Compare Match, the timer will be cleared

//take in user input
//change OCR1A - change only when interrupts are off
//Have something that can visualize the change
//Make pin flash faster or slower- and way to completely shut down pin
//Go a couple of times and then wait
//Pseudo-code

//user_input = input // user enters in Hz
//reg_clock = 62. 5 // nanoseconds
//pre_scaler = 256
//mod_clock = reg_clock * pre_scaler
//f_user = user_input * 1000000
//OCR1A = round((f_user/mod_clock)/2)
//set OCR1A

//TCCR1A- 16 bits- 65535- 62.5 ns each bit

#define ledPin 9

#define BAUDRATE 9600
#define MAX_CMD_SIZE 96
#define ENABLE_TIMER_INTERRUPTS() TIMSK1 |= (1<<OCIE1A)
#define DISABLE_TIMER_INTERRUPTS() TIMSK1 &= ~(1<<OCIE1A)

int serial_count = 0;
char serial_char;
char cmdbuffer[MAX_CMD_SIZE];
char *strchr_pointer;
int cmdlen = 0;

float reg_clock = 62.5;
int pre_scaler = 256;
int mod_clock = 16; // microseconds
int counts;
int isr_count = 0;

// ============ Sub-routines ========== //
boolean code_seen(char code) {
  strchr_pointer = strchr(cmdbuffer, code);
  return (strchr_pointer != NULL);
}

float code_value() {
  return (strtod(&cmdbuffer[strchr_pointer - cmdbuffer + 1], NULL));
}

void get_commands() {

  while (Serial.available() > 0) {

    serial_char = Serial.read();

    if (serial_char == '\n' ||
        serial_char == '\r') {
      if (serial_count == 0) return;

      cmdbuffer[serial_count] = 0;
      serial_count = 0;
      Serial.println(cmdbuffer);
      cmdlen++;
    }
    else {
      cmdbuffer[serial_count++] = serial_char;
    }
  }
}

void process_commands() {
  float codenum_frequency;
  float codenum_times;
  if (code_seen('F')) {
    codenum_frequency = code_value();
    Serial.print("Frequency (Hz): ");
    Serial.println(codenum_frequency);
    set_OCR1A(codenum_frequency);
  }
  if (code_seen('N')) {
    codenum_times = code_value();
    Serial.print("Number of times ran: ");
    Serial.println(codenum_times);
    counts = codenum_times * 2;
    //ENABLE_TIMER_INTERRUPTS();
  }

}

void set_OCR1A(float freq) {

  //DISABLE_TIMER_INTERRUPTS();
  float f_user = 1000000 / freq; // Units are microseconds
  Serial.println(f_user / mod_clock);
  Serial.println(f_user / mod_clock / 2);
  Serial.println(round(f_user / mod_clock / 2));
  float set_OCR1A = round((f_user / mod_clock) / 2);
  Serial.println(set_OCR1A);
  OCR1A = set_OCR1A;
  Serial.print("OCR1A has been set to ");
  Serial.println(OCR1A, DEC);
  ENABLE_TIMER_INTERRUPTS();

}

ISR (TIMER1_COMPA_vect)
{
  if (isr_count < counts) {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //toggle
    isr_count++;
  }
  if (isr_count == counts) {
    DISABLE_TIMER_INTERRUPTS();
    isr_count = 0;
  }
}



// ============ Setup & Loop ========== //
void setup() {
  Serial.begin(BAUDRATE);
  timer_init();
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}
void loop() {

  get_commands();
  if (cmdlen) {
    process_commands();
    cmdlen--;
  }

}




void timer_init() {

  pinMode(ledPin, OUTPUT);

  //initialize timer 1
  //noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 1000;
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);
  //interrupts();
}



