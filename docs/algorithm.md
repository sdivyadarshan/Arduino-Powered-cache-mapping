# Algorithm and Operation

1. Initialize the Arduino Nano GPIO, I²C LCD and EEPROM.
2. Read the EEPROM validity marker. If valid, load the previously saved number.
3. NEXT increments the selected decimal digit from 0 through 9.
4. CONFIRM appends the selected digit to the current input (maximum four digits).
5. SAVE stores the entered value in EEPROM and clears the input buffer.
6. The user enters a query and presses CHECK.
7. If a valid saved value equals the query, display CACHE HIT and turn on the green LED.
8. Otherwise, display CACHE MISS and turn on the red LED.
9. Turn off the result LED and clear the query buffer for the next test.

## Important interpretation
This implementation is a **single-entry cache lookup demonstrator**. It teaches the basic hit/miss decision. It does not implement a multi-line direct-mapped or set-associative cache, tag/index/offset extraction, a replacement policy, or measured physical cache latency.
