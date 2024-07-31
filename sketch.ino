#include <Wire.h>
#include <LiquidCrystal.h>
#include <TM1637Display.h>

// Initialize the LCD and TM1637 display
LiquidCrystal lcd(2, 28, 22, 21, 20, 19);
TM1637Display display(3, 4); // Replace with the correct pins for CLK and DIO

void setup() {
  Wire.begin();     
  lcd.begin(16, 2);  

  pinMode(27, OUTPUT); // LED indicator
  pinMode(5, OUTPUT);  // Buzzer control
  pinMode(6, OUTPUT);  // Another output, possibly LED
  pinMode(13, OUTPUT); // Another output, possibly LED
  pinMode(9, INPUT);   // Sensor input

  // Initialize outputs to LOW
  digitalWrite(27, LOW);
  digitalWrite(13, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  noTone(5);

  int Det = digitalRead(9);
  
  if (Det == HIGH) {
    digitalWrite(27, HIGH);
    digitalWrite(13, HIGH);
    tone(5, 262, 250); // Active buzzer on pin 5
    delay(10000);

    lcd.setCursor(0, 0); 
    lcd.print("Intruder Detected!");

    lcd.setCursor(0, 1); 
    lcd.print("You have 1 minute");

    // Display "100" to indicate "1:00" minute
    display.showNumberDecEx(100, 0x80 >> 2, true);
    delay(1000);

    for (int i = 59; i >= 0; i--) {
      int minutes = i / 60;
      int seconds = i % 60; 
      int displayValue = minutes * 100 + seconds; 

      display.showNumberDecEx(displayValue, 0x80 >> 2, true); 
      delay(1000); 
    }
  } else {
    digitalWrite(13, LOW);
    noTone(5);
    digitalWrite(27, LOW);
  }
}
