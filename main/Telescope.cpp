#include "Telescope.h"

float gearRatioYaw = 14.5; // 725 (driven gear [(7 x 98) + 39]) / 50 (drive gear)
int stepsYaw = 3200; // stepsYaw per rotation | 200 (default) * 16 (microsteps)

// Read Serial for new yaw
float readSerial(float yaw) {
  if (Serial.available() > 1) {
    float parsedYaw = Serial.parseFloat();
    if (yaw != parsedYaw) {
      yaw = parsedYaw;
    }
  }
  return yaw;
}

// Current- / New- yaw difference
int calculateYaw(float currentYaw, float yaw) {
  return yaw - currentYaw;
}

// Yaw difference to motor steps
int calculateStepsYaw(float yaw) {
  float fraction = yaw / 360;
  float temp = gearRatioYaw / fraction;
  return temp * stepsYaw;
}