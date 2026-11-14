# Design Decisions

- **Arduino Nano:** low-cost controller with adequate digital I/O, I²C and built-in EEPROM.
- **I²C LCD:** reduces wiring compared with a parallel LCD interface.
- **Internal pull-ups:** buttons use `INPUT_PULLUP`, avoiding external pull-up resistors.
- **EEPROM persistence:** the saved demonstration value survives power-off.
- **LED status:** separate green and red indicators make the comparison result easy to see.
- **Single-entry scope:** the prototype keeps the concept approachable; future versions can add multiple cache lines, address fields and mapping policies.

## Scope clarification
The present hardware compares one entered query with one saved value. It demonstrates the basic cache HIT/MISS idea, not a complete CPU cache hierarchy or an actual high-speed memory benchmark.
