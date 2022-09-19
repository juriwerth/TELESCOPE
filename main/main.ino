#include "Telescope.h"

float currentYaw = 0.0;
float yaw = 0.0;
String seperator = " ";

void setup() {
  Serial.begin(9600);                                                     // Initialising serial com
  pinMode(5, OUTPUT);                                                     // Puls (1 [On + Off] Puls: 1 step)
  pinMode(2, OUTPUT);                                                     // Direction of rotation
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT);
  pinMode(6, HIGH); 
  pinMode(7, LOW); 
  pinMode(8, LOW); 
}

void loop() {
  yaw = readSerial(yaw);                                              // Read serial for new yaw
  int diffYaw = calculateYaw(currentYaw, yaw);                    // Current- / new- yaw difference
  int steps = calculateStepsYaw(diffYaw);                             // Yaw difference to motor steps
  
  Serial.println("Steps: " + seperator + steps);
  (steps > 0) ? digitalWrite(2 ,HIGH) : digitalWrite(2 ,LOW);             // Set direction of rotation
  for (int step = 0; step < ((steps > 0) ? steps : steps * -1); step++) { // Loop through every step
    digitalWrite(5, HIGH);
    delayMicroseconds(500);
    digitalWrite(5, LOW);
    delayMicroseconds(500);
  }

  //Serial.println(currentYaw + seperator + yaw);
  currentYaw = yaw;
}