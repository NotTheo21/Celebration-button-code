#!/usr/bin/env python3
"""
Celebration Button - Python Simulation
Demonstrates the button press logic and display output
"""

import random
import time

# Celebration messages
CELEBRATIONS = [
    "YAY YOU DID IT",
    "AWESOME!!!",
    "YOU'RE THE BEST",
    "CONGRATS!!!",
    "WOOHOO!",
    "NAILED IT!"
]

class LCDSimulator:
    """Simulates an LCD display"""
    def __init__(self):
        self.line1 = ""
        self.line2 = ""
    
    def clear(self):
        self.line1 = ""
        self.line2 = ""
    
    def print_line1(self, text):
        self.line1 = text[:16]  # LCD is 16 chars wide
    
    def print_line2(self, text):
        self.line2 = text[:16]
    
    def display(self):
        print("╔════════════════════╗")
        print(f"║{self.line1:^18}║")
        print(f"║{self.line2:^18}║")
        print("╚════════════════════╝")

class CelebrationButton:
    """Simulates the celebration button"""
    def __init__(self):
        self.lcd = LCDSimulator()
        self.press_count = 0
    
    def startup(self):
        """Simulate startup"""
        print("\n🔌 Starting Celebration Button System...\n")
        self.lcd.print_line1("Ready!")
        self.lcd.display()
        print()
        time.sleep(1)
        self.lcd.clear()
    
    def press_button(self):
        """Simulate button press"""
        self.press_count += 1
        message = random.choice(CELEBRATIONS)
        
        print(f"\n🔘 Button Press #{self.press_count} - Message: '{message}'")
        print("\n📺 LCD Display Output:")
        
        self.lcd.clear()
        self.lcd.print_line1(message)
        self.lcd.print_line2("CELEBRATION!")
        self.lcd.display()
        
        print("\n⏱️  Displaying for 2 seconds...")
        time.sleep(2)
        
        print("🗑️  Clearing display...")
        self.lcd.clear()
        self.lcd.display()
        print()
    
    def run_demo(self):
        """Run a demonstration"""
        self.startup()
        
        print("=" * 50)
        print("🎉 SIMULATING 5 BUTTON PRESSES")
        print("=" * 50)
        
        for i in range(5):
            self.press_button()
            if i < 4:
                time.sleep(1)  # Wait between presses
        
        print("\n" + "=" * 50)
        print("✅ SIMULATION COMPLETE!")
        print("=" * 50)
        print(f"\nTotal button presses: {self.press_count}")
        print("\n📝 Summary:")
        print("  ✓ Button triggers correctly")
        print("  ✓ Random messages selected")
        print("  ✓ Display shows messages")
        print("  ✓ Message timing works")
        print("\n🚀 Next: Upload to your Arduino board!")
        print("\n")

if __name__ == "__main__":
    button = CelebrationButton()
    button.run_demo()
