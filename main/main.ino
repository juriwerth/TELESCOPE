#include "Telescope.h"  // Importing the library

void setup() {
  Serial.begin(9600);  // Initialising serial com
  pinMode(pulsYaw, OUTPUT);  // Puls (1 [On + Off] Puls: 1 step)
  pinMode(dirYaw, OUTPUT);  // Direction of rotation pin
  pinMode(pulsPitch, OUTPUT);  // Puls (1 [On + Off] Puls: 1 step)
  pinMode(dirPitch, OUTPUT);  // Direction of rotation pin
  pinMode(switch0, INPUT);  // 0 Degree switch
  pinMode(switch90, INPUT);  // 90 Degree switch
  pinMode(resetBtn, INPUT);  // Reset button
}

void loop() {
  if (!polar) {  // Check if polar boolian is false
    Serial.println("Enter the coodinates of the polar star: ");  // Serial printing
    polarPitch = readSerial(polarPitch, 0);  // Serial reading the value for polarPitch
    polarYaw = readSerial(polarYaw, 1);  // Serial reading the value for polarYaw
  }
  if (reset) {
    pitch = readSerial(pitch, 0);
    yaw = readSerial(yaw, 1);
    reset = false;
  }
  if (currentPitch != pitch) {
    deltaPitch = calculateDelta(currentPitch, pitch);
    deltaYaw = calculateDelta(currentYaw, yaw);
    stepsPitch = calculateStepsPitch(deltaPitch);
    stepsYaw = calculateStepsYaw(deltaYaw);
  }

  stepsPitch = direction(stepsPitch, dirPitch);  // Setting motor rotation
  stepsYaw = direction(stepsYaw, dirYaw);  // Setting motor rotation

  (!prep) ? prep = preperation(dirPitch, pulsPitch) : true;  // Telescope alignment
  (stepsPitch + stepsYaw < 1) ? algorithm(currentPitch, currentYaw, &pitch, &yaw) : true;  //Tracking algorithm

  while (stepsPitch + stepsYaw > 0 && !reset) {  // While steps > 0 and reset is false
    (digitalRead(resetBtn) == HIGH  || (digitalRead(switch0) == HIGH and digitalRead(switch90) == HIGH)) ? reset = true : true;  // Checking the resetPin, if HIGH, setting reset true 

    Serial.println("Pitch: " + String(stepsPitch) + seperator + "Yaw: " + String(stepsYaw));  // Serial printing the pitch and yaw steps
    while (digitalRead(switch90) == LOW) {}  // Pause if the 90 Degree switch is active

    stepsPitch = executeSteps(stepsPitch, pulsPitch, 0);  // Executing pitch steps
    stepsYaw = executeSteps(stepsYaw, pulsYaw, 1);  // Executing yaw steps
  }

  currentPitch = pitch;  // Setting the currentPitch value to pitch
  currentYaw = yaw;  // Setting the currentYaw value tp yaw
}
