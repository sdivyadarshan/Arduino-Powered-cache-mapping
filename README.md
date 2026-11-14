# Arduino-Powered Cache Mapping Prototype
## For Demonstrating High-Speed Memory Access

An interactive Arduino Nano educational prototype that demonstrates the basic cache lookup concept through a saved value, a user-entered query, and visible **HIT / MISS** feedback.

## Project at a glance
The user enters a number and saves it as the prototype's cached value. The value is retained in the Nano's EEPROM. The user then enters a query and presses CHECK. A matching value produces **CACHE HIT** (green LED); a different value produces **CACHE MISS** (red LED). A 16×2 I²C LCD displays the current input and result.

> **Scope note:** This is a single-entry cache lookup demonstrator. It explains the basic HIT/MISS decision; it does not implement multi-line direct-mapped or set-associative cache structures, tag/index/offset extraction, a replacement policy, or a physical cache-latency benchmark.

## Hardware
- Arduino Nano (ATmega328P)
- 16×2 LCD with I²C backpack
- Four push buttons: NEXT, CONFIRM, SAVE, CHECK
- Green HIT LED and red MISS LED
- 220 Ω current-limiting resistor for each external LED
- Breadboard, jumper wires and USB cable

## Button controls

| Button | Function |
|---|---|
| 1 | CONFIRM – append selected digit |
| 2 | SAVE – store current number in EEPROM |
| 3 | NEXT – cycle selected digit 0–9 |
| 4 | CHECK – compare query with saved value |

## Pin mapping

| Signal | Nano pin |
|---|---|
| NEXT | D8 |
| CONFIRM | D9 |
| SAVE | D10 |
| CHECK | D11 |
| Green HIT LED | D12 |
| Red MISS LED | D13 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC / GND | 5V / GND |

The buttons use `INPUT_PULLUP` and connect their input pin to GND when pressed. The sketch assumes LCD I²C address `0x27`; update it if an I²C scan reports another address.

## Repository structure

```text
.
├── README.md
├── src/
│   └── cache_mapping.ino
├── hardware/
│   ├── pinout.csv
│   └── wiring-and-components.md
├── docs/
│   ├── algorithm.md
│   ├── system-architecture.md
│   ├── design-decisions.md
│   ├── testing.md
│   ├── contribution-and-ai-disclosure.md
│   └── future-scope.md
├── media/
│   └── README.md
└── .gitignore
```

## Software requirements
- Arduino IDE
- Board package: Arduino AVR Boards
- Board selection: Arduino Nano
- Processor: select **ATmega328P (Old Bootloader)** if required by the particular Nano clone
- Library: **LiquidCrystal I2C** (Frank de Brabander)
- `Wire` and `EEPROM` are included with the Arduino AVR core

## Documentation
- [Wiring and components](hardware/wiring-and-components.md)
- [Algorithm](docs/algorithm.md)
- [System architecture](docs/system-architecture.md)
- [Design decisions](docs/design-decisions.md)
- [Testing checklist](docs/testing.md)
- [Contributions and AI disclosure](docs/contribution-and-ai-disclosure.md)
- [Future scope](docs/future-scope.md)

## Testing status
The testing checklist is provided for repeatable validation. Do not interpret the checklist as proof that every test has been independently recorded. Add measured observations after testing.

## Contributions and AI disclosure
The project owner carried out the project selection, component procurement, physical assembly, wiring, upload and hands-on troubleshooting. AI assistance supported conceptual explanation, code drafting/refinement, troubleshooting and documentation. The committed sketch is labelled as a reconstructed reference implementation based on the project discussion; compare it with the exact locally tested sketch before claiming byte-for-byte provenance. See [the disclosure](docs/contribution-and-ai-disclosure.md).

## License
No license has been added. A license should be selected only after the project owner confirms the intended reuse permissions for all included material.
