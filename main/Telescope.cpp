#include "Telescope.h"

const float gearRatioPitch = 14.5;
const int microstepsPitch = 3200;
const float gearRatioYaw = 14.5; // 725 (driven gear [(7 x 98) + 39]) / 50 (drive gear)
const int microstepsYaw = 3200; // stepsYaw per rotation | 200 (default) * 16 (microsteps)

// Read Serial for new yaw
float readSerial(float rotation, bool identification) {
  float temp = rotation;
  if (identification == 0) {Serial.println("Please enter a PITCH value (0 - 90) ");}
  else {Serial.println("Please enter a YAW value (0 - 360) ");}
  while (rotation == temp) {
    if (Serial.available() > 1) {
      float parsedFloat = Serial.parseFloat();
      rotation = parsedFloat;
    }
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
  float fraction = delta / 360.0;
  float temp = gearRatioPitch / fraction;
  return long(temp * microstepsPitch);
}

// Yaw delta to motor steps
long calculateStepsYaw(float delta) {
  float fraction = delta / 360.0;
  float temp = gearRatioYaw / fraction;
  return long(temp * microstepsYaw);
}
