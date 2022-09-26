## TELESCOPE:
Smart telescope algorithm and robotic

🔭 + 🤖 = 🪐

<details><summary>readSerial()</summary>
<p>

```c++
// Read Serial for new yaw
float readSerial(float rotation, bool identificator) {
  float temp = rotation;
  if (identificator == 0) {Serial.println("Please enter a PITCH value (0 - 90) ");}
  else {Serial.println("Please enter a YAW value (0 - 360) ");}
  while (rotation == temp) {
    if (Serial.available() > 1) {
      float parsedFloat = Serial.parseFloat();
      rotation = parsedFloat;
    }
  }
  if (rotation > 360) {
    int fit = rotation / 360.0;
    rotation = rotation - (360 * fit);
  }
  Serial.println(rotation);
  return rotation;
}
```

</p>
</details>

<details><summary>calculateDelta()</summary>
<p>

```c++
// Current / New delta
float calculateDelta(float current, float rotation) {
  return rotation - current;
}
```

</p>
</details>

<details><summary>calculateStepsPitch()</summary>
<p>

```c++
// Pitch delta to motor steps
long calculateStepsPitch(float delta) {
  float fraction = delta / 90.0;
  return fullRotationPitch * fraction;
}
```

</p>
</details>

<details><summary>caculateStepsYaw()</summary>
<p>

```c++
// Yaw delta to motor steps
long calculateStepsYaw(float delta) {
  float fraction = delta / 360.0;
  float temp = gearRatioYaw * fraction;
  return temp * microstepsYaw;
}
```

</p>
</details>

<details><summary>direction()</summary>
<p>

```c++
long direction(long steps, int dirPin) {
  if (steps > 0) {
    digitalWrite(dirPin, HIGH);
    return steps;
  } else {
    digitalWrite(dirPin, LOW);
    return stepsPitch * -1;
  }
}
```

</p>
</details>

<details><summary>alorithm()</summary>
<p>

```c++
float alorithm(float polarPitch, float polarYaw, float currentPitch, float currentYaw, float *pitch, float *yaw) {
  if (millis() - currentMillis >= 15000) {  // jede 15 sec 0,0625 grad bewegen
    unsigned int diffPitch = (polarPitch > currentPitch) ? polarPitch - currentPitch: currentPitch - polarPitch;
    unsigned int diffYaw = (polarYaw > currentYaw) ? polarYaw - currentYaw: currentYaw - polarYaw;
    unsigned int radius = sqrt(radiusPitch * radiusPitch + radiusYaw * radiusYaw);
    float angle = atan(diffYaw / diffPitch);
    *pitch = radius * sin(angle + 0.0625);
    *yaw = radius * cos(angle + 0.0625);
    currentMillis = millis();
  }
}
```

</p>
</details>

<details><summary>preperation()</summary>
<p>

```c++
bool preperation(int dir, int puls) {
  digitalWrite(dir, LOW);
  while (digitalRead(switch0) == LOW) {
    Serial.println("Aligning the TELESCOPE ...");
    digitalWrite(puls, HIGH);
    delayMicroseconds(500);
    digitalWrite(puls, LOW);
    delayMicroseconds(500);
  }
  return true;
}
```

</p>
</details>

<details><summary>executeSteps()</summary>
<p>

```c++
// Execute steps 
long executeSteps(long steps, int puls, bool identificator) {
  if (steps > 0) {
      digitalWrite(puls, HIGH);
      delayMicroseconds(500);
      digitalWrite(puls, LOW);
      delayMicroseconds(500);
      if (identificator == 0) {
        if (digitalRead(switch0) == HIGH) {
          (steps > 0) ? steps -= 1 : steps += 1;
        }
      } else {
        (steps > 0) ? steps -= 1 : steps += 1;
      }
    }
  return steps;
}
```

</p>
</details>
