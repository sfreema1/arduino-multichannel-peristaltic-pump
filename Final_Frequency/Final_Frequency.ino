#define ledPin 13

#define BAUDRATE 9600 
#define MAX_CMD_SIZE 96
#define ENABLE_TIMER_INTERRUPTS() TIMSK1 |= (1<<OCIE1A)
#define DISABLE_TIMER_INTERRUPTS() TIMSK1 &= ~(1<<OCIE1A)

// setting up serial monitor, command line size, enable timer interrupts and other stuff

int serial_count = 0; // initialize to 0
char serial_char;//initialize
char cmdbuffer[MAX_CMD_SIZE];
char *strchr_pointer;
int cmdlen = 0;

float reg_clock = 62.5; 
int pre_scaler = 256;
int mod_clock = 16; // microseconds
int counts; // initialize
int isr_count = 0;

// ============ Sub-routines ========== //
boolean code_seen(char code) { 
  strchr_pointer = strchr(cmdbuffer, code);// return first instance of char in array
  return (strchr_pointer != NULL);//returns if not NULL
}

float code_value() {
  return (strtod(&cmdbuffer[strchr_pointer - cmdbuffer + 1], NULL)); 
}

void get_commands() {

  while (Serial.available() > 0) { 

    serial_char = Serial.read(); //reads the code

    if (serial_char == '\n' || //if new line or return 
        serial_char == '\r') {
      if (serial_count == 0) return; //sets count to 0

      cmdbuffer[serial_count] = 0; //set command buffer to 0
      serial_count = 0;//serial_count to 0
      Serial.println(cmdbuffer);//print cmdbuffer
      cmdlen++;
    }
    else {
      cmdbuffer[serial_count++] = serial_char; //else adds char to cmdbuffer
    }
  }
}

void process_commands() {
  float codenum_frequency;
  float codenum_times;
  if (code_seen('F')) { # if setting F, frequency
    codenum_frequency = code_value(); 
    Serial.print("Frequency (Hz): "); // Frequency can go from 1 Hz to 31250 Hz
    Serial.println(codenum_frequency);
    set_OCR1A(codenum_frequency);
  }
  if (code_seen('N')) {//If you are setting N, # of times ran,
    codenum_times = code_value();
    Serial.print("Number of times ran: "); //put back ISR and turn on/off interrupts
    Serial.println(codenum_times);// tell # of times
    counts = codenum_times * 2; 
    ENABLE_TIMER_INTERRUPTS();#turn on interrupts
  }
}


void set_OCR1A(float freq) {
  DISABLE_TIMER_INTERRUPTS();//disable interrupts
  float f_user = 1000000 / freq; // Units are microseconds
  Serial.println(f_user / mod_clock);
  Serial.println(f_user / mod_clock / 2);
  Serial.println(round(f_user / mod_clock / 2));
  float set_OCR1A = round((f_user / mod_clock) / 2);//calculations to get frequency
  Serial.println(set_OCR1A);//print Output Compare Register
  OCR1A = set_OCR1A;//set Output Compare Register
  Serial.print("OCR1A has been set to ");
  Serial.println(OCR1A, DEC);
  ENABLE_TIMER_INTERRUPTS();//turn on interrupts

}
ISR (TIMER1_COMPA_vect) // Interrupt Service Routine
{
  if (isr_count < counts) { // if the routine is currently running
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1); //toggle
    Serial.println("Hit first if");//This runs 200 times for a 100 input, is that right?
    //I think this is right, since 200 times in that 1/2 second then 0 for the other half?
    isr_count++;
  }
  if (isr_count == counts) { //if the routine finishes, the second if should print
    DISABLE_TIMER_INTERRUPTS();
    Serial.println("Hit Second if"); // This runs as soon as the program starts or any F is entered
    isr_count = 0; // set back to 0
  }
}
// ============ Setup & Loop ========== //
void setup() {
  Serial.begin(BAUDRATE); // Setup for serial connection
  pinMode(9, OUTPUT); // setup pin 9
  pinMode(10, OUTPUT);// setup pin 10 
  pinMode(ledPin,OUTPUT);//setup ledPin
  // CTC Mode - Top is OCR1A
  // Mode WGM13 = 0 | WGM12 = 1 | WGM11 = 0 | WGM10 = 0
  // COM1A1/COM1B1 = 0
  // COM1A0/COM1B0 = 1
  // 256 Presccaler = CS12 ON TCCR1B = 1
  TCCR1A = B01010000; // Timer Counter Control 1 Channel A setup bits
  TCCR1B = B00001100; // Timer Count Control 1 Channel B setup bits
  OCR1A = 180; // Output Compare Register 1
  TCNT1 = 0; // Timer / Counter Register
  TIMSK1 |= (1 << OCIE1A); // Timer/Counter Interrupt Mask Register 1 
}

void loop() {
  get_commands(); //reference fxn
  if (cmdlen) { // if there are commands
    process_commands(); // reference fxn to process
    cmdlen--; //subtract 1 
  }
}

