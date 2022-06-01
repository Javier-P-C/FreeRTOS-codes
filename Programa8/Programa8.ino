#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
#define RED 6
#define YELLOW 7
#define BLUE 8


LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  xTaskCreate(redLedTask, "Red Led Task", 128, NULL, 1, NULL);
  xTaskCreate(yellowLedTask, "Yellow Led Task", 128, NULL, 1, NULL);
  xTaskCreate(blueLedTask, "Blue Led Task", 128, NULL, 1, NULL);
  xTaskCreate(TaskAnalogRead, "AnalogRead" ,  128 ,  NULL ,  1  ,  NULL );
  


}
  void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    lcd.clear();
    lcd.setCursor(0,0);
    // print out the value you read:
    Serial.println(sensorValue*5/1024);
    lcd.print(sensorValue);
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
void redLedTask(){
  pinMode(RED, OUTPUT);
  while(1){
    digitalWrite(RED,digitalRead(RED)^1);
    //Serial.println("This is Red");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }

void yellowLedTask(){
  pinMode(YELLOW, OUTPUT);
  while(1){
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    //Serial.println("This is Yellow");
    
    vTaskDelay(500/portTICK_PERIOD_MS);
    }
  }
void blueLedTask(){
  pinMode(BLUE, OUTPUT);
  while(1){
    digitalWrite(BLUE,digitalRead(BLUE)^1);
    //Serial.println("This is Blue");
    vTaskDelay(250/portTICK_PERIOD_MS);
    }
  }

void loop() {
  
}
