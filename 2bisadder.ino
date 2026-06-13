// --- Output Pins (Sending signals TO your hardware circuit) ---
const int pinA0 = 3;  // FIXED: Changed from 1 to 3 to avoid USB/Serial conflicts!
const int pinA1 = 2;  // Number A - MSB
const int pinB0 = 4;  // Number B - LSB
const int pinB1 = 5;  // Number B - MSB
const int pinM  = 6;  // Control Bit: 0 = Add, 1 = Subtract

void setup() {
  pinMode(pinA0, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinB0, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinM,  OUTPUT);

  Serial.begin(9600);
  
  // Clear any trailing text on startup
  Serial.println(); 
} 

void loop() {
  // Loop through Control Bit: 0 = Addition, 1 = Subtraction
  for (int m = 0; m <= 1; m++) {
    
    // UPDATED: Loop through values for A from 2 to 4
    for (int valA = 0; valA <= 1; valA++) {
      
      // UPDATED: Loop through values for B from 2 to 4
      for (int valB = 0; valB <= 1; valB++) {
        
        // 1. Send the physical signals to your circuit
        digitalWrite(pinM,  m);
        
        digitalWrite(pinA0, bitRead(valA, 0)); 
        digitalWrite(pinA1, bitRead(valA, 1)); 

        digitalWrite(pinB0, bitRead(valB, 0)); 
        digitalWrite(pinB1, bitRead(valB, 1)); 

        // 2. Calculate expected math using standard positive inputs
        int totalResult;
        if (m == 0) {
          totalResult = valA + valB; // Handles equations like 2 + 2 = 4
        } else {
          totalResult = valA - valB; // Handles equations like 4 - 2 = 2
        }

        // 3. Print the equation and the answer cleanly
        Serial.print(valA);
        Serial.print(m == 0 ? " + " : " - ");
        Serial.print(valB);
        Serial.print(" = ");
        Serial.println(totalResult); 

        // Wait 6 seconds so you can look at your hardware circuit outputs/LEDs
        delay(6000);
      }
    }
  }
  
  Serial.println("\nDone\n");
  delay(6000);
}
