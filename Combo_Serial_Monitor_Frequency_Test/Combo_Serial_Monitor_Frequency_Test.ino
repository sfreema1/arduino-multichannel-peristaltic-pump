#define BAUDRATE 9600
#define MAX_CMD_SIZE 96

#include "TimerOne.h"

#define PWM_PIN 10
#define INTERRUPT_PIN 9

char strchr_pointer;
char serial_char;
char cmdbuffer[MAX_CMD_SIZE]; // stores the characters
int serial_count = 0;//count # of character cming in
int cmdlen = 0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE); //BAUDRATE is the bits per second

  pinMode(INTERRUPT_PIN, OUTPUT);
  Timer1.initialize(1000);
  Timer1.pwm(PWM_PIN,512);
  Timer1.attachInterrupt(callback);

}

void callback()
{
  digitalWrite(INTERRUPT_PIN, digitalRead(INTERRUPT_PIN) ^ 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  //Serial Availabe checks incoming- 1 true, 0 false
  {
    serial_char = Serial.read(); //reads and saves to serial_char
    if(isdigit(serial_char) != 0){
      Serial.println("okay");
    }
    else{
      Serial.println("not okay");
    }
    }
    if (serial_char == '\n' || //if new line or return
        serial_char == '\r')
    {
      cmdbuffer[serial_count] = 0;//sets last letter to 0
      serial_count = 0;//sets count to 0
      frequency = strtol(cmdbuffer,NULL,10); 
      Timer1.setPeriod(frequency);
      // Whole message has been read and now can be process
      Serial.println(frequency,DEC); //DEC is decimal
    }
  else
  {
    cmdbuffer[serial_count++] = serial_char;//adds one to buffer
  }

}


