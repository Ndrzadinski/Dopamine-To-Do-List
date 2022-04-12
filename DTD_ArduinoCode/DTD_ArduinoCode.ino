/*
 * Nathan Drzadinski
 * 3/12/22
 * Dopamine To Do List
 * 
 * 3 BUTTONS, 1 LCD DISPLAY, 2 LED
 * 
 *
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define OnOff 2       // On off button
#define Reset 8       // Resets Daily Tasks
#define BigButton 12  // Task complete button (Opposite)
#define BlueColor 9   // Blue color of RGB LED 
#define GreenColor 10 // Green color of RGB LED
#define RedColor 11   // Red color of RGB LED


int numTasks = 9;
//Create List of Daily Tasks
String Tasks[] = {
/* Morning */
"Push-ups",
"Take a shower",
"Brush & Floss",
"Get Dressed",
"Grab food to eat",

/* Evening */
"Set up Tomorrow",
"Brush & Floss",
"Push-ups",
"Read"
};

LiquidCrystal_I2C lcd(0x27,20,4);

int OnOffState = 0;
int ResetState = 0;
int BigButtonState = 0;

int taskcount = 0;

void complete();

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("Hello");
  lcd.setCursor(5,1);
  lcd.print("World!");
  
  pinMode(OnOff, INPUT);
  pinMode(Reset, INPUT);
  pinMode(BigButton, INPUT);
    
  pinMode(BlueColor, OUTPUT);
  pinMode(GreenColor, OUTPUT);
  pinMode(RedColor, OUTPUT);
  
}

void loop() {
  // read the state of the buttons value:
  OnOffState = digitalRead(OnOff);
  ResetState = digitalRead(Reset);
  BigButtonState = digitalRead(BigButton);

  if (BigButtonState == LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    if (taskcount >= numTasks){
      lcd.print("Tasks Complete!");
    }
    else{
      lcd.print(Tasks[taskcount]);
      complete();
    }
    taskcount++;
  }
  else if (ResetState == HIGH){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Reseting");
    delay(500);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print(Tasks[0]);
    taskcount = 1;
  }
}

void complete(){
  for(int i=0; i<255; i++){
    analogWrite(RedColor, i);
    analogWrite(BlueColor, 255-i);
    if (i<128){
      analogWrite(GreenColor, 128-i);
    }
    else{
      analogWrite(GreenColor, i-128);
    }
    delay(2);
  }
  
  for(int i=255; i>0; i--){
    analogWrite(RedColor, i);
    analogWrite(BlueColor, 255-i);
    if (i<128){
      analogWrite(GreenColor, 255-i);
    }
    else{
      analogWrite(GreenColor, 383-i);
    }
    delay(2);
  }
  analogWrite(RedColor, 0);
  analogWrite(BlueColor, 0);
  analogWrite(GreenColor, 0);
}
