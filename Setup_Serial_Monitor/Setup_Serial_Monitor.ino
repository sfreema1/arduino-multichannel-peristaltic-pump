#define BAUDRATE 9600
#define MAX_CMD_SIZE 96

char serial_char;
char cmdbuffer[MAX_CMD_SIZE]; // stores the characters
int serial_count = 0;//count # of character cming in

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE); //BAUDRATE is the bits per second

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  //Serial Availabe checks incoming- 1 true, 0 false
  {
    serial_char = Serial.read(); //reads and saves to serial_char

    if (serial_char == '\n' || //if new line or return
        serial_char == '\r')
    {
      cmdbuffer[serial_count] = 0;//sets last letter to 0
      serial_count = 0;//sets count to 0
      // Whole message has been read and now can be process
      Serial.println(cmdbuffer);
      if (strcmp(cmdbuffer, "bye") == 0) {
        //strcmp compares strings
        Serial.println("Success");
      }
  }
  else
  {
    cmdbuffer[serial_count++] = serial_char;//adds one to buffer
  }

}
}




