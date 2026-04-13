# Celebration Button Setup Guide

## Quick Start

1. **Connect Button to PCB:**
   - Button pin → Arduino pin 2 (or modify `BUTTON_PIN` in code)
   - Other button pin → GND (ground)

2. **Connect Display to PCB:**
   - See specific display type below

3. **Upload Code:**
   - Open `celebration_button.ino` in Arduino IDE
   - Select correct board and port
   - Click Upload

4. **Test:** Press the button to see "YAY YOU DID IT" on your display!

---

## Display Connection Options

### Option 1: LCD 16x2/20x4 with I2C Module (Most Common)
**Wiring:**
```
LCD I2C Module → Arduino
VCC → 5V
GND → GND
SDA → A4 (Uno) or SDA pin (other boards)
SCL → A5 (Uno) or SCL pin (other boards)
```

**Arduino IDE Setup:**
1. Go to Sketch → Include Library → Manage Libraries
2. Search for "LiquidCrystal I2C" by Frank de Brabander
3. Click Install
4. Code is already set for this - just upload!

**If display doesn't work:**
- Find your I2C address: [Use this guide](https://create.arduino.cc/editor/arduino_official/sketches/0DFb86e2dcd3aa7d2f2e)
- Replace `0x27` in line 10 with your address

---

### Option 2: LCD with Parallel Connection
**Wiring:**
```
LCD → Arduino
RS → pin 12
E → pin 11
D4 → pin 5
D5 → pin 4
D6 → pin 3
D7 → pin 2
VSS → GND
VCC → 5V
```

**Code Change:**
Replace line 10 in `celebration_button.ino` with:
```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

Also change button pin to: `const int BUTTON_PIN = 6;`

---

### Option 3: OLED Display (SSD1306)
**Wiring:**
```
OLED → Arduino
GND → GND
VCC → 5V
SCL → A5 (Uno)
SDA → A4 (Uno)
```

**Arduino IDE Setup:**
1. Manage Libraries → Search "Adafruit SSD1306"
2. Install it (and "Adafruit GFX" when prompted)

**Code Changes:**
Replace lines 6-10 with:
```cpp
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// In setup():
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.display();
delay(1000);

// In displayCelebration(), replace lcd.print() with:
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println(celebrations[messageIndex]);
display.display();
```

---

## Button Troubleshooting

**Button not responding?**
- Check wire connections to pin 2 and GND
- Try changing `BUTTON_PIN` to a different pin
- Increase `DEBOUNCE_DELAY` if it's triggering multiple times

**Button triggers randomly?**
- Add a 10µF capacitor between button pin and GND
- Increase `DEBOUNCE_DELAY` to 100

---

## Customization

### Add More Messages
Edit the `celebrations[]` array around line 30:
```cpp
const char* celebrations[] = {
  "YAY YOU DID IT",
  "AWESOME!!!",
  "ADD YOUR OWN MESSAGE HERE"
};
```

### Change Display Time
Modify the `delay(2000)` values (2000 = 2 seconds)

### Add Sound
Connect a buzzer to another pin and add:
```cpp
digitalWrite(BUZZER_PIN, HIGH);
delay(200);
digitalWrite(BUZZER_PIN, LOW);
```

---

## Need Help?

Let me know:
1. What board are you using? (Arduino Uno, Mega, etc?)
2. What type of display? (LCD, OLED, other?)
3. Any error messages from Arduino IDE?
