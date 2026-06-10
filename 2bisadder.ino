
// --- Output Pins (Sending signals TO your hardware circuit) ---
const int pinA0 = 1;  // CHANGED FROM 1 TO 3 to avoid USB conflict!
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
    
    // Loop through all values for A: 0, 1, 2, 3
    for (int valA = 0; valA <= 3; valA++) {
      
      // Loop through all values for B: 0, 1, 2, 3
      for (int valB = 0; valB <= 3; valB++) {
        
        // 1. Send the physical signals to your circuit
        digitalWrite(pinM,  m);
        
        digitalWrite(pinA0, bitRead(valA, 0)); 
        digitalWrite(pinA1, bitRead(valA, 1)); 

        digitalWrite(pinB0, bitRead(valB, 0)); 
        digitalWrite(pinB1, bitRead(valB, 1)); 

        // 2. Convert raw loop integers to signed 2's complement values
        int signedA = twosCompValue(valA); 
        int signedB = twosCompValue(valB); 
        
        // 3. Calculate expected math
        int totalResult;
        if (m == 0) {
          totalResult = signedA + signedB;
        } else {
          totalResult = signedA - signedB;
        }

        // 4. Print the equation and the answer cleanly
        Serial.print(signedA);
        Serial.print(m == 0 ? " + " : " - ");
        Serial.print(signedB);
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

// 2-bit binary integer to 2's complement decimal converter
int twosCompValue(int binary2bit) {
  if (binary2bit >= 2) {
    return binary2bit - 4;  // 2 (10) becomes -2, 3 (11) becomes -1
  }
  return binary2bit;        // 0 (00) stays 0, 1 (01) stays 1
}