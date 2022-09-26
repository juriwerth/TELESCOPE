#include "Telescope.h"

// Setup
void setup() {
  Serial.begin(9600);
  pinMode(pulsYaw, OUTPUT);
  pinMode(dirYaw, OUTPUT);
  pinMode(pulsPitch, OUTPUT);
  pinMode(dirPitch, OUTPUT);
  pinMode(pitch2Enable, OUTPUT);
  pinMode(switch0, INPUT);
  pinMode(switch90, INPUT);
  pinMode(resetBtn, INPUT);
}

// Main loop
void loop() {
  // Checking if polar boolian is false
  if (!polar) {
    Serial.println("Enter the coodinates of the polar star: ");
    polarPitch = readSerial(polarPitch, 0);
    polarYaw = readSerial(polarYaw, 1);
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
  (!prep) ? prep = preperation(dirPitch, pulsPitch, pulsPitch2) : true;
  (stepsPitch + stepsYaw < 1) ? algorithm(currentPitch, currentYaw, &pitch, &yaw) : true;

  // Looping threw the folloing code wihle steps > 0 and reset is false
  while (stepsPitch + stepsYaw > 0 && !reset) {
    // If the reset button or switches are pressed, reset becomes true
    (digitalRead(resetBtn) == HIGH  || (digitalRead(switch0) == HIGH and digitalRead(switch90) == HIGH)) ? reset = true : true;

    // Serial printing pitch and yaw values
    Serial.println("Pitch: " + String(stepsPitch) + seperator + "Yaw: " + String(stepsYaw));
    while (digitalRead(switch90) == LOW) {} 

    // Executing motor steps
    stepsPitch = executeSteps(stepsPitch, pulsPitch, 0);
    stepsYaw = executeSteps(stepsYaw, pulsYaw, 1);
  }

  // Setting the current values to the new values
  currentPitch = pitch;
  currentYaw = yaw;
}
