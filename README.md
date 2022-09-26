TELESCOPE:
Smart telescope algorithm and robotic

🪐 = 🔭 + 🤖

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
