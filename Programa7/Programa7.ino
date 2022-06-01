#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 6
#define YELLOW 7
#define BLUE 8

SemaphoreHandle_t xSemaphore;

void setup() {
  Serial.begin(9600);
  xSemaphore=xSemaphoreCreateBinary();
  xSemaphoreGive(xSemaphore);
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
      xSemaphoreTake(xSemaphore,10);
      Serial.println("This is Red");
      xSemaphoreGive(xSemaphore);
      vTaskDelay(1);
  }
}

void yellowLedTask()
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
      digitalWrite(YELLOW,digitalRead(YELLOW)^1);
      xSemaphoreTake(xSemaphore,10);
      Serial.println("This is Yellow");
      xSemaphoreGive(xSemaphore);
      vTaskDelay(1);
  }
}

void blueLedTask()
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
      digitalWrite(BLUE,digitalRead(BLUE)^1);
      xSemaphoreTake(xSemaphore,10); //Toma semáforo con tiempo de espera máximo de 10x15mseg=150mseg
      Serial.println("This is Blue");
      xSemaphoreGive(xSemaphore);
      vTaskDelay(1);
  }
}

void loop() {
}
