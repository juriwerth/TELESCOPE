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
inline float polarPitch;
inline float polarYaw;
inline bool polar = false;
inline bool prep = true;
inline bool reset = true;
const inline String seperator = " ";

const inline int pulsPitch = 22;
const inline int pulsPitch2 = 5;
const inline int dirPitch = 23;
const inline int pulsYaw = 26;
const inline int dirYaw = 25;
const inline int switch0 = 32; 
const inline int switch90 = 33;
const inline int pitch2Enable = 19;

float readSerial(float rotation, bool identification);
float calculateDelta(float current, float rotation);
long calculateStepsPitch(float delta);
long calculateStepsYaw(float delta);
long direction(long steps, int dirPin);
bool preparation(int dir, int plus, int puls2, int pitch2Enable);
void algorithm(float polarPitch, float polarYaw, float currentPitch, float currentYaw, float *pitch, float *yaw);
long executeSteps(long steps, int puls, bool identificator);

#endif

