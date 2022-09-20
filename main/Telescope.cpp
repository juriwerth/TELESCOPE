#include "Telescope.h"

void setup() {
  Serial.begin(9600);                                                 // Initialising serial com
  pinMode(pulsYaw, OUTPUT);                                                     // Puls (1 [On + Off] Puls: 1 step)
  pinMode(dirYaw, OUTPUT);                                                     // Direction of rotation
  pinMode(pulsPitch, OUTPUT);
  pinMode(dirPitch, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {
  pitch = readSerial(pitch, 0);
  yaw = readSerial(yaw, 1);
  deltaPitch = calculateDelta(currentPitch, pitch);
  deltaYaw = calculateDelta(currentYaw, yaw);
  stepsPitch = calculateStepsPitch(deltaPitch);
  stepsYaw = calculateStepsYaw(deltaYaw);

  Serial.println("#####################################################");
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

  while (stepsPitch + stepsYaw > 0) {
    Serial.println("Pitch: " + String(stepsPitch) + seperator + "Yaw: " + String(stepsYaw));
    while (!digitalRead(switchPin)) {}
    if (stepsPitch > 0) {
      digitalWrite(pulsPitch, HIGH);
      delayMicroseconds(500);
      digitalWrite(pulsPitch, LOW);
      delayMicroseconds(500);
      (stepsPitch > 0) ? stepsPitch -= 1 : stepsPitch += 1;
    }
    if (stepsYaw > 0) {
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
