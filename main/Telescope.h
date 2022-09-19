#ifndef TELESCOPE_H
#define TELESCOPE_H

#include <Arduino.h>

inline int deltaPitch;
inline int deltaYaw;
inline int stepsPitch;
inline int stepsYaw;

float readSerial(float pitch, float yaw);

int calculateDelta(float currentPitch, float pitch, float currentYaw, float yaw);
int calculateSteps(float pitch, float yaw);

#endif
