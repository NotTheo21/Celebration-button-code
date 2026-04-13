/*
  TEST & SIMULATION FILE
  This is a C++ simulation to test the celebration button logic
  without needing actual Arduino hardware
  
  Compile with: g++ -o test_celebration test_simulation.cpp
  Run with: ./test_celebration
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

// ============== SIMULATED MESSAGES ==============
const char* celebrations[] = {
  "YAY YOU DID IT",
  "AWESOME!!!",
  "YOU'RE THE BEST",
  "CONGRATS!!!",
  "WOOHOO!",
  "NAILED IT!"
};
const int numCelebrations = 6;

// ============== SIMULATED BUTTON STATE ==============
int lastButtonState = 1;  // HIGH
const int DEBOUNCE_DELAY = 50;  // milliseconds
int simulatedButtonPresses = 0;

// ============== DISPLAY SIMULATION ==============
void displayCelebration(int messageIndex) {
  cout << "\n";
  cout << "╔════════════════════════════════════╗\n";
  cout << "║  LCD DISPLAY OUTPUT:               ║\n";
  cout << "╠════════════════════════════════════╣\n";
  cout << "║ " << celebrations[messageIndex];
  
  // Pad with spaces to fill 16 character width (LCD display width)
  int padding = 16 - string(celebrations[messageIndex]).length();
  for (int i = 0; i < padding; i++) cout << " ";
  cout << " ║\n";
  
  cout << "║ CELEBRATION!                       ║\n";
  cout << "╚════════════════════════════════════╝\n";
  cout << "\n";
}

// ============== SIMULATION FUNCTION ==============
void simulateButtonPress() {
  int messageIndex = rand() % numCelebrations;
  simulatedButtonPresses++;
  
  cout << "═══════════════════════════════════════\n";
  cout << "BUTTON PRESS #" << simulatedButtonPresses << " DETECTED!\n";
  cout << "═══════════════════════════════════════\n";
  
  displayCelebration(messageIndex);
  
  cout << "Message sent: \"" << celebrations[messageIndex] << "\"\n";
  cout << "Waiting for debounce...\n";
}

// ============== MAIN TEST ==============
int main() {
  srand(time(0));
  
  cout << "\n";
  cout << "╔═══════════════════════════════════════╗\n";
  cout << "║  CELEBRATION BUTTON - SIMULATION     ║\n";
  cout << "║  Testing Button & Display Logic      ║\n";
  cout << "╚═══════════════════════════════════════╝\n";
  cout << "\n";
  
  cout << "Available celebration messages:\n";
  for (int i = 0; i < numCelebrations; i++) {
    cout << "  " << (i + 1) << ". " << celebrations[i] << "\n";
  }
  cout << "\n";
  
  cout << "Simulating 5 button presses...\n";
  cout << "(In real hardware, each press triggers a random message)\n";
  cout << "\n";
  
  // Simulate 5 button presses
  for (int i = 0; i < 5; i++) {
    simulateButtonPress();
    sleep(1);  // Wait 1 second between presses
  }
  
  cout << "═══════════════════════════════════════\n";
  cout << "✓ SIMULATION COMPLETE\n";
  cout << "═══════════════════════════════════════\n";
  cout << "\nTotal button presses simulated: " << simulatedButtonPresses << "\n";
  cout << "\nNEXT STEP:\n";
  cout << "1. Upload 'celebration_button.ino' to your Arduino board\n";
  cout << "2. Press your physical button to trigger celebratory messages!\n";
  cout << "\n";
  
  return 0;
}
