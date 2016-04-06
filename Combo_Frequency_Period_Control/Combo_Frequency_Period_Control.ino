#define BAUDRATE 9600
#define MAX_CMD_SIZE 96

#include "TimerOne.h"

#define PWM_PIN 10
#define INTERRUPT_PIN 9

int serial_count = 0;
char serial_char;
char cmdbuffer[MAX_CMD_SIZE];
char *strchr_pointer;
int cmdlen = 0;

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
  unsigned int codenum;
  if (code_seen('D')) {
    codenum = code_value();
    Serial.print("Duty Cycle (%): ");
    Serial.println(codenum);
    setPwmDuty(PWM_PIN, codenum) //Duty cycle is from 0 to 1023
  }
  if (code_seen('F')) {
    codenum = code_value();
    Serial.print("Frequency (Hz): "); // frequency should from 0 to 1000000
    Serial.print(codenum);
    Timer1.setperiod(codenum);
  }
}

void callback()
{
  digitalWrite(INTERRUPT_PIN, digitalRead(INTERRUPT_PIN) ^ 1);
}

// ============ Setup & Loop ========== //
void setup() {
  Serial.begin(BAUDRATE);

  pinMode(INTERRUPT_PIN, OUTPUT);
  Timer1.initialize(1000);
  Timer1.pwm(PWM_PIN,512);
  Timer1.attachInterrupt(callback);
}

void loop() {

  get_commands();
  if (cmdlen) {
    process_commands();
    cmdlen--;
  }

}

