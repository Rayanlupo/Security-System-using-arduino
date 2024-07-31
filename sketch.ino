#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  Wire.begin();     
  lcd.begin(16, 2);  
  lcd.backlight();   


  pinMode(24, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);


  digitalWrite(24, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(13, LOW);

}

void loop() {
  lcd.setCursor(0, 0); 
  lcd.print("Hello, world!");

  lcd.setCursor(0, 1); 
  lcd.print("Raspberry Pi Pico");

  int Det = digitalRead(12);
  
  if (Det == HIGH) {
    digitalWrite(24, HIGH);
    tone(5, 262, 250); 
    delay(10000);
  } else {
    digitalWrite(24, LOW);
    digitalWrite(5, LOW);
  }
}
