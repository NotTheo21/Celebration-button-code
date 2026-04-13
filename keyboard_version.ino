/*
  KEYBOARD CELEBRATION BUTTON (USB Version)
  Makes the button appear as a keyboard key to your computer
  Works with Arduino Leonardo, Arduino Micro, or similar boards with USB support
  
  When button is pressed, it sends text to the computer as if typed on a keyboard
*/

// ============ COMPATIBLE BOARDS ============
// This code works on:
// - Arduino Leonardo
// - Arduino Micro
// - Arduino Due
// - Arduino MKR board family
// 
// NOT compatible with Arduino Uno/Nano (they don't have USB keyboard support)

#include <Keyboard.h>

// ============ PIN DEFINITIONS ============
const int BUTTON_PIN = 2;           // Pin where button is connected
const int DEBOUNCE_DELAY = 50;      // Debounce time in ms
const int REPEAT_DELAY = 2000;      // Delay between button presses (ms)

// ============ MESSAGES TO TYPE ============
const char* messages[] = {
  "YAY YOU DID IT",
  "AWESOME!!!",
  "YOU'RE THE BEST",
  "CONGRATS!!!",
  "WOOHOO!",
  "NAILED IT!"
};
const int numMessages = 6;

// ============ VARIABLES ============
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long lastPressTime = 0;

// ============ SETUP ============
void setup() {
  Serial.begin(9600);
  
  // Initialize button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize keyboard
  Keyboard.begin();
  
  Serial.println("Keyboard Celebration Button Ready!");
  delay(2000);
}

// ============ MAIN LOOP ============
void loop() {
  // Read button state with debouncing
  int buttonReading = digitalRead(BUTTON_PIN);
  
  // If button state changed, reset the debounce timer
  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // After debounce delay, check if button is actually pressed
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (buttonReading == LOW && (millis() - lastPressTime) > REPEAT_DELAY) {
      typeRandomMessage();
      lastPressTime = millis();
      Serial.println("Button pressed - message typed!");
    }
  }
  
  lastButtonState = buttonReading;
}

// ============ TYPE A RANDOM MESSAGE ============
void typeRandomMessage() {
  int msgIndex = random(0, numMessages);
  
  // Type the message
  Keyboard.print(messages[msgIndex]);
  
  // Press Enter at the end
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

// ============ ALTERNATIVE: ADD MODIFIERS ============
// Uncomment to modify behavior:

/*
void typeWithModifiers() {
  // Type message in CAPS LOCK
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.print("YAY YOU DID IT");
  Keyboard.releaseAll();
}

// Send text to a specific application (Discord, Slack, etc.)
void sendDiscordMessage() {
  // This assumes Discord window is active
  Keyboard.print("YAY YOU DID IT!");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}
*/
