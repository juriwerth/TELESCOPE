#ifndef TELESCOPE_H
#define TELESCOPE_H

#include <Arduino.h>

inline float pitch;
inline float yaw;
inline float currentPitch;
inline float currentYaw;
inline long stepsPitch;
inline long stepsYaw;
inline float deltaPitch;
inline float deltaYaw;
const inline float polarPitch;
const inline float polarYaw;
inline bool polar = false;
inline bool prep = false;
inline bool reset = true;
const inline String seperator = " ";

const inline int pulsPitch = 2;
const inline int dirPitch = 3;
const inline int pulsYaw = 4;
const inline int dirYaw = 5;
const inline int switch0 = 12;
const inline int switch90 = 13;
const inline int resetBtn = 11;

float readSerial(float rotation, bool identification);
float calculateDelta(float current, float rotation);
long calculateStepsPitch(float delta);
long calculateStepsYaw(float delta);
bool preperatrion(int dir, int plus);
long direction(long steps, int dirPin)
long executeSteps(long steps, int puls, bool identificator);

#endif
