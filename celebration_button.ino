/*
  CELEBRATION BUTTON CODE
  Triggers celebratory messages on a display when a button is pressed
  
  This code works with Arduino boards and an LCD display.
  Modify pin numbers and library based on your specific hardware.
*/

// ============== LIBRARY SETUP ==============
// Uncomment the display library that matches YOUR hardware:

// For 16x2/20x4 LCD with I2C module:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 is common I2C address, 16x2 is size

// For other display types, use one of these instead:
// #include <LiquidCrystal.h>  // For parallel LCD
// #include <Adafruit_SSD1306.h>  // For OLED displays

// ============== PIN DEFINITIONS ==============
const int BUTTON_PIN = 2;           // Pin where button is connected (adjust as needed)
const int DEBOUNCE_DELAY = 50;      // Debounce time in ms

// ============== CELEBRATION MESSAGES ==============
const char* celebrations[] = {
  "YAY YOU DID IT",
  "AWESOME!!!",
  "YOU'RE THE BEST",
  "CONGRATS!!!",
  "WOOHOO!",
  "NAILED IT!"
};
const int numCelebrations = 6;

// ============== VARIABLES ==============
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
int messageIndex = 0;

// ============== SETUP ==============
void setup() {
  // Initialize serial for debugging (optional)
  Serial.begin(9600);
  Serial.println("Celebration Button Starting...");
  
  // Initialize Wire (I2C) for LCD communication
  Wire.begin();
  delay(100);
  
  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize LCD display
  lcd.init();
  lcd.backlight();
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Ready!");
  delay(1000);
  lcd.clear();
}

// ============== MAIN LOOP ==============
void loop() {
  // Read button state with debouncing
  int buttonReading = digitalRead(BUTTON_PIN);
  
  // If button state changed, reset the debounce timer
  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // After debounce delay, check if button is actually pressed
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (buttonReading == LOW) {  // Button pressed (LOW because of PULLUP)
      displayCelebration();
      delay(500);  // Prevent multiple triggers
    }
  }
  
  lastButtonState = buttonReading;
}

// ============== DISPLAY CELEBRATION ==============
void displayCelebration() {
  // Get a random celebration message
  messageIndex = random(0, numCelebrations);
  
  // Clear display and show message
  lcd.clear();
  lcd.print(celebrations[messageIndex]);
  
  // Scroll effect (optional - adjust as needed)
  delay(2000);
  
  // Show second line with extra fun
  lcd.setCursor(0, 1);
  lcd.print("CELEBRATION!");
  
  delay(2000);
  lcd.clear();
  
  // Print to serial monitor for debugging
  Serial.print("Button pressed! Message: ");
  Serial.println(celebrations[messageIndex]);
}
