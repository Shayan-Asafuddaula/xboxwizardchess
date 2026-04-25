// Serial pins mapped to the ESP-01S
const int TX_PIN = 0;
const int RX_PIN = 1;

// Motor 1 (Wheel 1)
const int PWM_1 = 2; const int DIR_1A = 3; const int DIR_1B = 4;
// Motor 2 (Wheel 2)
const int PWM_2 = 5; const int DIR_2A = 6; const int DIR_2B = 7;
// Motor 3 (Wheel 3)
const int PWM_3 = 8; const int DIR_3A = 9; const int DIR_3B = 10;

void setup() {
  Serial.begin(115200); // For USB debugging
  
  // Setup communication with ESP-01S
  Serial1.setRX(RX_PIN);
  Serial1.setTX(TX_PIN);
  Serial1.begin(115200);

  // Initialize motor pins
  pinMode(PWM_1, OUTPUT); pinMode(DIR_1A, OUTPUT); pinMode(DIR_1B, OUTPUT);
  pinMode(PWM_2, OUTPUT); pinMode(DIR_2A, OUTPUT); pinMode(DIR_2B, OUTPUT);
  pinMode(PWM_3, OUTPUT); pinMode(DIR_3A, OUTPUT); pinMode(DIR_3B, OUTPUT);
  
  // Ensure all motors start stopped
  analogWrite(PWM_1, 0); analogWrite(PWM_2, 0); analogWrite(PWM_3, 0);
}

void loop() {
  // We expect a 9-byte packet: 'W', 'I', 'Z', D1, S1, D2, S2, D3, S3
  if (Serial1.available() >= 9) {
    
    // Check for the "WIZ" header
    if (Serial1.read() == 'W') {
      if (Serial1.read() == 'I') {
        if (Serial1.read() == 'Z') {
          
          // Read the motor commands
          int d1 = Serial1.read(); int s1 = Serial1.read();
          int d2 = Serial1.read(); int s2 = Serial1.read();
          int d3 = Serial1.read(); int s3 = Serial1.read();

          // Apply to Motor 1
          digitalWrite(DIR_1A, d1 == 1 ? HIGH : LOW);
          digitalWrite(DIR_1B, d1 == 1 ? LOW : HIGH);
          analogWrite(PWM_1, s1);

          // Apply to Motor 2
          digitalWrite(DIR_2A, d2 == 1 ? HIGH : LOW);
          digitalWrite(DIR_2B, d2 == 1 ? LOW : HIGH);
          analogWrite(PWM_2, s2);

          // Apply to Motor 3
          digitalWrite(DIR_3A, d3 == 1 ? HIGH : LOW);
          digitalWrite(DIR_3B, d3 == 1 ? LOW : HIGH);
          analogWrite(PWM_3, s3);
        }
      }
    }
  }
}