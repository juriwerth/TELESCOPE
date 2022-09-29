#include "Telescope.h"

// Setup
void setup() {
  Serial.begin(115200);
  pinMode(pulsPitch, OUTPUT);
  pinMode(pulsPitch2, OUTPUT);
  pinMode(dirPitch, OUTPUT);
  pinMode(pulsYaw, OUTPUT);
  pinMode(dirYaw, OUTPUT);
  pinMode(pitchEnable, OUTPUT);
  pinMode(pitch2Enable, OUTPUT);
  pinMode(switch0, INPUT_PULLUP);
  pinMode(switch90, INPUT_PULLUP);
}

// Main loop
void loop() {
  // Checking if polar boolian is false
  if (!polar) {
    Serial.println("Enter the coodinates of the polar star: ");
    polarPitch = readSerial(polarPitch, 0);
    polarYaw = readSerial(polarYaw, 1);
    polar = true;
  }

  // Checking if the reset boolian is true
  if (reset) { 
    pitch = readSerial(pitch, 0);
    yaw = readSerial(yaw, 1);
    reset = false;
  }

  // Checking if the values currentPitch and pitch are not equal
  if (currentPitch != pitch) {
    deltaPitch = calculateDelta(currentPitch, pitch);
    deltaYaw = calculateDelta(currentYaw, yaw);
    stepsPitch = calculateStepsPitch(deltaPitch);
    stepsYaw = calculateStepsYaw(deltaYaw);
  }

  // Setting the rotation direction of the motors
  stepsPitch = direction(stepsPitch, dirPitch);
  stepsYaw = direction(stepsYaw, dirYaw);

  // Checking if the prep boolian is false
  (!prep) ? prep = preparation(pulsPitch, dirPitch, pulsPitch2, pitch2Enable) : true;
  if (stepsPitch + stepsYaw < 1) {
    algorithm(polarPitch, polarYaw, currentPitch, currentYaw, &pitch, &yaw);
  }

  digitalWrite(pitchEnable, LOW);
  digitalWrite(pitch2Enable, LOW);

  // Looping threw the folloing code wihle steps > 0 and reset is false
  while (stepsPitch + stepsYaw > 0 && !reset) {
    // If the reset button or switches are pressed, reset becomes true
    ((digitalRead(switch0) == LOW and digitalRead(switch90) == LOW)) ? reset = true : true;

    // Serial printing pitch and yaw values
    Serial.println("Pitch: " + String(stepsPitch) + seperator + "Yaw: " + String(stepsYaw));
    //while (digitalRead(switch90) == LOW) {}

    // Executing motor steps
    stepsPitch = executeSteps(stepsPitch, pulsPitch2, 0);
    long _ = executeSteps(stepsPitch, pulsPitch, 0);
    stepsYaw = executeSteps(stepsYaw, pulsYaw, 1);
  }

  // Setting the current values to the new values
  currentPitch = pitch;
  currentYaw = yaw;
}
