// Includes the Servo library for motor control
#include <Servo.h>

// Define constants for Ultrasonic Sensor pins and motor control
#define ULTRASONIC_TRIG_PIN 10  // Pin for triggering the ultrasonic pulse
#define ULTRASONIC_ECHO_PIN 11  // Pin for receiving the ultrasonic echo
#define SERVO_PIN 12            // Pin to which the servo motor is attached

// Define variables for time measurement and calculated distance
#define SOUND_SPEED 0.034       // Speed of sound in cm per microsecond (340 m/s)

long timeInterval;              // Variable to store pulse duration
int measuredDistance;           // Variable to store calculated distance

Servo motorControl;             // Servo object to control motor movement

// Initial setup routine
void setup() {
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT); // Configure the trigger pin as an output
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);  // Configure the echo pin as an input
  Serial.begin(9600);                   // Initialize serial communication
  motorControl.attach(SERVO_PIN);       // Attach the servo object to its designated pin
}

// Main loop routine
void loop() {
  // Sweep servo from 15 to 165 degrees and measure distance
  for (int angle = 15; angle <= 165; angle++) {
    motorControl.write(angle);  // Rotate servo to current angle
    delay(25);                  // Wait for servo to reach position
    measuredDistance = getDistance(); // Get distance from ultrasonic sensor
    
    Serial.print(angle);        // Print current servo angle
    Serial.print(",");          // Print separator for data parsing
    Serial.print(measuredDistance); // Print distance value
    Serial.print(".");          // Print separator for data parsing
  }

  // Sweep servo back from 165 to 15 degrees
  for (int angle = 165; angle > 15; angle--) {
    motorControl.write(angle);  // Rotate servo back to current angle
    delay(25);                  // Wait for servo to reach position
    measuredDistance = getDistance(); // Get distance again
    
    Serial.print(angle);        // Print angle while moving back
    Serial.print(",");          // Print separator
    Serial.print(measuredDistance); // Print measured distance
    Serial.print(".");          // Print separator
  }
}

// Function to calculate the distance from ultrasonic sensor
int getDistance() {
  // Start trigger pulse
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  // Set trigger pin to LOW to reset
  delayMicroseconds(2);                    // Short delay to ensure clean pulse
  
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH); // Start a pulse with trigger HIGH
  delayMicroseconds(10);                   // Pulse duration of 10 microseconds
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);  // End pulse by setting LOW
  
  timeInterval = pulseIn(ULTRASONIC_ECHO_PIN, HIGH); // Measure time of pulse
  
  // Calculate distance (in cm) based on time and speed of sound
  measuredDistance = timeInterval * SOUND_SPEED / 2;
  return measuredDistance;  // Return calculated distance
}
