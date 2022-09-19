#include "Telescope.h"

float currentYaw = 0.0;
float yaw = 0.0;
float currentPitch = 0.0;
float pitch = 0.0;

String seperator = " ";

int pulsYaw = 2;
int dirYaw = 3;
int pulsPitch = 5;
int dirPitch = 6;

void setup() {
  Serial.begin(9600);                                                     // Initialising serial com
  pinMode(5, OUTPUT);                                                     // Puls (1 [On + Off] Puls: 1 step)
  pinMode(2, OUTPUT);                                                     // Direction of rotation
}

void loop() {
  (pitch, yaw) = readSerial(pitch, yaw);                                  // Read serial for new yaw
  (deltaPitch, deltaYaw) = calculateDelta(currentPitch, pitch, currentYaw, yaw);  // Current / New delta
  (stepsPitch, stepsYaw) = calculateSteps(deltaPitch, deltaYaw);                        // Yaw difference to motor steps
  
  //Serial.println("Pitch: " + seperator + deltaPitch + seperator + "Yaw: " + seperator + stepsYaw);
  (stepsPitch > 0) ? digitalWrite(dirPitch, HIGH) : digitalWrite(dirPitch ,LOW);             // Set direction of rotation
  (stepsYaw > 0)  ? digitalWrite(dirYaw ,HIGH) : digitalWrite(dirYaw ,LOW); 

  (stepsPitch < 0) ? stepsPitch *= -1 : true;
  (stepsYaw < 0) ? stepsYaw *= -1 : true;

  while (stepsPitch + stepsYaw > 0) {
    Serial.println("Pitch: " + seperator + stepsPitch + seperator + "Yaw: " + seperator + stepsYaw);
    if (stepsPitch) {
      digitalWrite(pulsPitch, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulsPitch, LOW);
      delayMicroseconds(500);
      (stepsPitch > 0) ? stepsPitch -= 1 : stepsPitch += 1;
    }
    if (stepsYaw) {
      digitalWrite(pulsYaw, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulsYaw, LOW);
      delayMicroseconds(500);
      (stepsYaw > 0) ? stepsYaw -= 1 : stepsYaw += 1;
    }
  }

  currentPitch = pitch;
  currentYaw = yaw;
}
