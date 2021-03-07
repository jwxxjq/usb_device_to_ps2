//Source: http://dduino.blogspot.com/2011/11/arduino-ps2-emulator-computer-control.html

//KBD stuff
#include <ps2dev.h>  // to emulate a PS/2 device
PS2dev keyboard(2,4);  // PS2dev object (4:data, 2:clock)
int enabled = 0;  // pseudo variable for state of "keyboard"
unsigned char c;  //char stores data recieved from computer for KBD

//Sonar stuff
//const int numReadings = 5;   // set a variable for the number of readings to take
//int index = 0;                // the index of the current reading
//int total = 0;                // the total of all readings
//int average = 0;              // the average
//int oldAverage = 0;           // the old average
//int echoPin = 6;              // the SRF05's echo pin
//int trigPin = 7;              // the SRF05's init pin
//unsigned long pulseTime = 0;  // variable for reading the pulse
//unsigned long distance = 0;   // variable for storing distance
//bool init_done = 1;

void ack()
{
  //acknowledge commands
  while(keyboard.write(0xFA));
}

int keyboardcommand(unsigned char command)
{
  unsigned char val;
  keyboard.keyboard_reply(command, &val);
  return 0;
}

void setup()
{
  // send the keyboard start up
  while(keyboard.write(0xAA)!=0);
  delay(10);
  // make the init pin an output:
//  pinMode(trigPin, OUTPUT);
  // make the echo pin an input:
//  pinMode(echoPin, INPUT);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop()
{
  unsigned char leds;
  //if host device wants to send a command:
  if (keyboard.init_done == 0)
  {
    if((digitalRead(4)==LOW) || (digitalRead(2) == LOW))
    {
      keyboard.keyboard_handle(&leds);
    }
  }
  else
  {
    if (keyboard.init_done == 1){
      Serial.println("write start");

      delay(1000);
      while((digitalRead(2) == HIGH)){};
      while((digitalRead(2) == LOW)){};
      while(keyboard.keyboard_press_special(PS2dev::RIGHT_CONTROL)){
        keyboard.keyboard_handle(&leds);
      };
      delay(100);
      while(keyboard.keyboard_release_special(PS2dev::RIGHT_CONTROL)){
        keyboard.keyboard_handle(&leds);
      };
      
      delay(300);
      
      while((digitalRead(2) == HIGH)){};
      while((digitalRead(2) == LOW)){};
      while(keyboard.keyboard_press_special(PS2dev::RIGHT_CONTROL)){
        keyboard.keyboard_handle(&leds);
      };
      delay(100);
      while(keyboard.keyboard_release_special(PS2dev::RIGHT_CONTROL)){
        keyboard.keyboard_handle(&leds);
      };
      Serial.println("write end");
    }
    delay(10);
  }
}
