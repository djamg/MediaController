#include <ClickEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>

#define ENCODER_DT A1
#define ENCODER_SW A2
#define PIN1 2
#define PIN2 3
#define PIN3 4
#define PIN4 5
#define ENCODER_CLK A0

ClickEncoder *encoder; 
int16_t last, value; 

void timerIsr() {
  encoder->service();
}

void setup() {
  Serial.begin(9600);
  Consumer.begin(); 
  encoder = new ClickEncoder(ENCODER_DT, ENCODER_CLK, ENCODER_SW); 

  Timer1.initialize(1000); 
  Timer1.attachInterrupt(timerIsr); 
  last = -1;
  pinMode(PIN1, INPUT_PULLUP);
  pinMode(PIN2, INPUT_PULLUP);
  pinMode(PIN3, INPUT_PULLUP);
  pinMode(PIN4, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
} 

void loop() {  
  value += encoder->getValue();

  if (value != last) {
    if(last<value) //
      Consumer.write(MEDIA_VOLUME_UP);
      else
      Consumer.write(MEDIA_VOLUME_DOWN);
    last = value;

  }

  if(digitalRead(PIN1)==LOW){
    Consumer.write(MEDIA_PLAY_PAUSE);
    delay(300);
  }

  if(digitalRead(PIN2)==LOW){
    Consumer.write(HID_CONSUMER_SCAN_NEXT_TRACK);
    delay(300);
  }

  if(digitalRead(PIN3)==LOW){
    Consumer.write(HID_CONSUMER_SCAN_PREVIOUS_TRACK);
    delay(300);
  }

    if(digitalRead(PIN4)==LOW){
    Consumer.write(CONSUMER_EXPLORER);
    delay(300);
  }

  delay(10);
}

        
