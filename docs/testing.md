# Testing Checklist

Mark each item only after performing the test on the assembled hardware.

- [ ] Nano powers up over USB.
- [ ] LCD backlight and text are visible.
- [ ] LCD I²C address is confirmed as 0x27 (or sketch updated to the detected address).
- [ ] NEXT cycles the selected digit from 0 to 9.
- [ ] CONFIRM appends digits in the correct order.
- [ ] SAVE stores a non-empty number and shows confirmation.
- [ ] Saved value remains after power is disconnected and restored.
- [ ] Query equal to saved value produces CACHE HIT and green LED.
- [ ] Query different from saved value produces CACHE MISS and red LED.
- [ ] LEDs turn off after the result display interval.
- [ ] Repeated button presses are stable and do not cause unintended multiple inputs.

## Results
No measured timing, hit-rate statistics or independent test results are asserted in this repository. Record actual observations here after testing.
