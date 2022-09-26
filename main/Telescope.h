#ifndef TELESCOPE_H
#define TELESCOPE_H

#include <Arduino.h>

inline float pitch;
inline float currentPitch;
inline float yaw;
inline float currentYaw;
inline long stepsPitch;
inline long stepsYaw;
inline float deltaPitch;
inline float deltaYaw;
inline bool prep = false;
const inline String seperator = " ";

const inline int pulsYaw = 2;
const inline int dirYaw = 3;
const inline int pulsPitch = 4;
const inline int dirPitch = 5;
const inline int switch0 = 12;
const inline int switch90 = 13;

float readSerial(float rotation, bool identification);
float calculateDelta(float current, float rotation);
long calculateStepsPitch(float delta);
long calculateStepsYaw(float delta);
long executeSteps(long steps, int puls, bool identificator);

#endif
