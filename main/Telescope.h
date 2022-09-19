#ifndef TELESCOPE_H
#define TELESCOPE_H

#include <Arduino.h>

float readSerial(float yaw);

// Pitch
//int calculateYaw(float currentYaw, float yaw);
//int calculateStepsYaw(float yaw);

// Yaw
int calculateYaw(float currentYaw, float yaw);
int calculateStepsYaw(float yaw);

#endif