// Signal-Shift-LED _ Ultra High Sensitivity
// Author: Moamen El-Sayed Abouhaty
// Description: Maps sound intensity to 6 LEDs like a battery level indicator

const int ledPins[6] = {12, 10, 8, 6, 4, 2};
const int micA0 = A0;

// Sensitivity: Decreasing this number makes it much more sensitive (try 5 to 15)
const int maxDelta = 12;  
int lastVal = 0;

void setup() {
  // Enable internal reference (1.1V) to increase reading accuracy by ~5x
  analogReference(INTERNAL); 
  
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(micA0);
  int delta = abs(val - lastVal);

  // Map the sound "strength" based on the new sensitivity
  int numLeds = map(delta, 2, maxDelta, 0, 6); 
  numLeds = constrain(numLeds, 0, 6);

  // Update LEDs to represent volume level
  for (int i = 0; i < 6; i++) {
    if (i < numLeds) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

  // Very fast update rate to capture slight sound variations
  lastVal = val;
  delay(5); 
}