# System Architecture

The prototype is organized into four functional layers:

- **Input layer:** four push buttons provide digit selection, digit confirmation, cache save and query check.
- **Controller layer:** Arduino Nano debounces inputs, builds the number, reads/writes EEPROM and compares the query.
- **Storage layer:** the Nano's EEPROM retains one saved demonstration value across power cycles.
- **Output layer:** the I²C LCD displays the operating state and result; green and red LEDs indicate HIT and MISS.

```text
Push Buttons
     |
     v
Arduino Nano Control Logic <----> EEPROM (saved value)
     |
     +------> I2C LCD (status / value / result)
     |
     +------> Green LED (HIT) / Red LED (MISS)
```

EEPROM is non-volatile microcontroller storage used here to preserve the demonstration value. It is not equivalent to CPU cache memory in speed, architecture or intended purpose.
