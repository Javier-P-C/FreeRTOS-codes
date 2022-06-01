#include <Arduino_FreeRTOS.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

void setup() {
  xTaskCreate(redLedTask,"Red Led Task",128,NULL,1,NULL);
  xTaskCreate(yellowLedTask,"Yellow Led Task",128,NULL,2,NULL);
  xTaskCreate(blueLedTask,"Blue Led Task",128,NULL,2,NULL);
  
  
  pinMode(YELLOW,OUTPUT);
  pinMode(BLUE,OUTPUT);
}

void redLedTask()
{
  pinMode(RED,OUTPUT);
  while(1)
  {
      digitalWrite(RED,digitalRead(RED)^1);
      delay(1);
  }
}

void yellowLedTask()
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
      digitalWrite(YELLOW,digitalRead(YELLOW)^1);
      delay(1);
  }
}

void blueLedTask()
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
      digitalWrite(BLUE,digitalRead(BLUE)^1);
      delay(1);
  }
}

void loop() {
}
