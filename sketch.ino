#include <Wire.h>
#include <LiquidCrystal.h>
#include <TM1637.h>

// Initialize the LCD and TM1637 display
LiquidCrystal lcd(2, 28, 22, 21, 20, 19);
TM1637 display(3, 4); // CLK and DIO pins for TM1637

void setup() {
  Wire.begin();
  lcd.begin(16, 2);

  pinMode(27, OUTPUT); // LED indicator
  pinMode(5, OUTPUT);  // Buzzer control
  pinMode(6, OUTPUT);  // LED indicator or another output
  pinMode(13, OUTPUT); // Another output, possibly LED
  pinMode(17, OUTPUT); // Another output, possibly LED (make sure 17 is available on your board)
  pinMode(9, INPUT);   // Sensor input

  // Initialize outputs to LOW
  digitalWrite(27, LOW);
  digitalWrite(13, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);

  display.set(); // Initialize the display
  display.init();
  display.setBrightness(7); // Set brightness level (0-7)
}

void loop() {
  noTone(5);

  int Det = digitalRead(9);

  if (Det == HIGH) {
    digitalWrite(27, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(17, HIGH);
    tone(5, 262, 250); // Active buzzer on pin 5
    delay(10000); // Initial delay after detection

    lcd.setCursor(0, 0);
    lcd.print("Intruder Detected!");

    lcd.setCursor(0, 1);
    lcd.print("You have 1 minute");

    // Start countdown from 60 seconds
    for (int i = 60; i >= 0; i--) {
      display.display(0, i / 10); // Tens place
      display.display(1, i % 10); // Units place

      delay(1000); // Wait for 1 second
    }
  } else {
    digitalWrite(27, LOW);
    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
    digitalWrite(17, LOW);
    noTone(5);
    display.clearDisplay(); // Clear the display when no intruder is detected
  }
}
