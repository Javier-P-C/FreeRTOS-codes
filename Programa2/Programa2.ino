#include <Arduino_FreeRTOS.h>

#define RED 5
#define YELLOW 7
#define BLUE 8

void setup() {
  Serial.begin(9600);
  xTaskCreate(redLedTask,"Red Led Task",128,NULL,1,NULL);
  xTaskCreate(yellowLedTask,"Yellow Led Task",128,NULL,1,NULL);
  xTaskCreate(blueLedTask,"Blue Led Task",128,NULL,1,NULL);
  
  
  pinMode(YELLOW,OUTPUT);
  pinMode(BLUE,OUTPUT);
}

void redLedTask()
{
  pinMode(RED,OUTPUT);
  while(1)
  {
      digitalWrite(RED,digitalRead(RED)^1);
      Serial.println("This is Red");
      delay(100);
  }
}

void yellowLedTask()
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
      digitalWrite(YELLOW,digitalRead(YELLOW)^1);
      Serial.println("This is Yellow");
      delay(100);
  }
}

void blueLedTask()
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
      digitalWrite(BLUE,digitalRead(BLUE)^1);
      Serial.println("This is Blue");
      delay(100);
  }
}

void loop() {
}
