#include "Telescope.h"

void setup() {
  Serial.begin(9600);                                                 // Initialising serial com
  pinMode(pulsYaw, OUTPUT);                                                     // Puls (1 [On + Off] Puls: 1 step)
  pinMode(dirYaw, OUTPUT);                                                     // Direction of rotation
  pinMode(pulsPitch, OUTPUT);
  pinMode(dirPitch, OUTPUT);
  pinMode(switch0, INPUT);
  pinMode(switch90, INPUT);
}

void loop() {
  pitch = readSerial(pitch, 0);
  yaw = readSerial(yaw, 1);
  deltaPitch = calculateDelta(currentPitch, pitch);
  deltaYaw = calculateDelta(currentYaw, yaw);
  stepsPitch = calculateStepsPitch(deltaPitch);
  stepsYaw = calculateStepsYaw(deltaYaw);

  if (stepsPitch > 0) {
    digitalWrite(dirPitch, HIGH);
  } else {
    digitalWrite(dirPitch, LOW);
    stepsPitch = stepsPitch * -1;
  }
  if (stepsYaw > 0) {
    digitalWrite(dirYaw, HIGH);
  } else {
    digitalWrite(dirYaw, LOW);
    stepsYaw = stepsYaw * -1;
  }

  //(!prep) ? preperation() : true;

  while (stepsPitch + stepsYaw > 0) {
    Serial.println("Pitch: " + String(stepsPitch) + seperator + "Yaw: " + String(stepsYaw));
    while (digitalRead(switch90) == LOW) {}

    stepsPitch = executeSteps(stepsPitch, pulsPitch, 0);
    stepsYaw = executeSteps(stepsYaw, pulsYaw, 1);
  }

  currentPitch = pitch;
  currentYaw = yaw;
}
