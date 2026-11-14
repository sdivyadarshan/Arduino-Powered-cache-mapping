# Wiring and Components

## Hardware
- Arduino Nano (ATmega328P)
- 16×2 LCD with I²C backpack
- Four momentary push buttons
- Green LED (HIT) and red LED (MISS)
- One 220 Ω current-limiting resistor per LED
- Breadboard, jumper wires and USB cable

## Pin connections

| Component | Arduino Nano |
|---|---|
| NEXT button | D8 to GND |
| CONFIRM button | D9 to GND |
| SAVE button | D10 to GND |
| CHECK button | D11 to GND |
| Green HIT LED | D12 through 220 Ω resistor to LED anode; cathode to GND |
| Red MISS LED | D13 through 220 Ω resistor to LED anode; cathode to GND |
| LCD SDA | A4 |
| LCD SCL | A5 |
| LCD VCC | 5V |
| LCD GND | GND |

Buttons use `INPUT_PULLUP`; each button must connect its assigned input pin to GND when pressed. The LCD sketch assumes I²C address `0x27`. If the address differs, run an I²C scanner and update the LCD constructor in the sketch.

Use a separate 220 Ω resistor in series with each external LED. The LCD backlight circuit does not replace these resistors.
