#include "TimerOne.h"

#define PWM_PIN 10
#define INTERRUPT_PIN 9

void setup()
{
  pinMode(INTERRUPT_PIN, OUTPUT);
  //Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  //Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  //Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt1
  Timer1.initialize(1000);
  Timer1.pwm(PWM_PIN,512);
  Timer1.attachInterrupt(callback);
}
 
void callback()
{
  digitalWrite(INTERRUPT_PIN, digitalRead(INTERRUPT_PIN) ^ 1);
}

void loop()
{

  
}

