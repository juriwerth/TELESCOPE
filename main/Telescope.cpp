#include "Telescope.h"

const float gearRatioPitch = 14.5;
const int microstepsPitch = 1600;
const float gearRatioYaw = 14.5; // 725 (driven gear [(7 x 98) + 39]) / 50 (drive gear)
const int microstepsYaw = 3200; // stepsYaw per rotation | 200 (default) * 16 (microsteps)
const float fullRotationPitch = 11900;

// Telescope alignment before commands
void preperation() {
  if (digitalRead(switch0) == LOW) {
    digitalWrite(pulsPitch, HIGH);
    delayMicroseconds(500);
    digitalWrite(pulsPitch, LOW);
    delayMicroseconds(500);
  }
}

// Read Serial for new yaw
float readSerial(float rotation, bool identificator) {
  float temp = rotation;
  if (identificator == 0) {Serial.println("Please enter a PITCH value (0 - 90) ");}
  else {Serial.println("Please enter a YAW value (0 - 360) ");}
  while (rotation == temp) {
    if (Serial.available() > 1) {
      float parsedFloat = Serial.parseFloat();
      rotation = parsedFloat;
    }
  }
  if (rotation > 360) {
    int fit = rotation / 360.0;
    rotation = rotation - (360 * fit);
  }
  Serial.println(rotation);
  return rotation;
}

// Current / New delta
float calculateDelta(float current, float rotation) {
  return rotation - current;
}

// Pitch delta to motor steps
long calculateStepsPitch(float delta) {
  float fraction = delta / 90.0;
  return fullRotationPitch * fraction;
}

// Yaw delta to motor steps
long calculateStepsYaw(float delta) {
  float fraction = delta / 360.0;
  float temp = gearRatioYaw * fraction;
  return temp * microstepsYaw;
}

// Execute steps 
long executeSteps(long steps, int puls, bool identificator) {
  if (steps > 0) {
      digitalWrite(puls, HIGH);
      delayMicroseconds(500);
      digitalWrite(puls, LOW);
      delayMicroseconds(500);
      if (identificator == 0) {
        if (digitalRead(switch0) == HIGH) {
          (steps > 0) ? steps -= 1 : steps += 1;
        }
      } else {
        (steps > 0) ? steps -= 1 : steps += 1;
      }
    }
  return steps;
}
