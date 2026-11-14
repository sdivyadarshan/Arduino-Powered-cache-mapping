#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// Arduino Nano - I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Push buttons (button connects the pin to GND when pressed)
const byte PIN_NEXT    = 8;
const byte PIN_CONFIRM = 9;
const byte PIN_SAVE    = 10;
const byte PIN_CHECK   = 11;

// Status LEDs
const byte PIN_GREEN = 12;  // Cache HIT
const byte PIN_RED   = 13;  // Cache MISS

// EEPROM layout
const int EEPROM_MAGIC_ADDR = 0;
const int EEPROM_VALUE_ADDR = 1;
const byte EEPROM_MAGIC = 0xA5;

const unsigned long DEBOUNCE_MS = 35;
const unsigned int MAX_VALUE = 9999;

struct ButtonState {
  byte pin;
  bool lastReading;
  bool stableState;
  unsigned long lastChange;
};

ButtonState buttons[4] = {
  {PIN_NEXT, HIGH, HIGH, 0},
  {PIN_CONFIRM, HIGH, HIGH, 0},
  {PIN_SAVE, HIGH, HIGH, 0},
  {PIN_CHECK, HIGH, HIGH, 0}
};

byte selectedDigit = 0;
unsigned int inputNumber = 0;
byte inputDigits = 0;
unsigned int cachedNumber = 0;
bool cacheValid = false;

bool pressed(byte index) {
  bool reading = digitalRead(buttons[index].pin);
  if (reading != buttons[index].lastReading) {
    buttons[index].lastChange = millis();
    buttons[index].lastReading = reading;
  }
  if ((millis() - buttons[index].lastChange) >= DEBOUNCE_MS) {
    if (reading != buttons[index].stableState) {
      buttons[index].stableState = reading;
      if (buttons[index].stableState == LOW) return true;
    }
  }
  return false;
}

void updateInputScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digit:");
  lcd.print(selectedDigit);
  lcd.print(" Input:");
  lcd.print(inputNumber);
  lcd.setCursor(0, 1);
  lcd.print("NEXT     CONFIRM");
}

void clearInput() {
  inputNumber = 0;
  inputDigits = 0;
}

void saveCache() {
  if (inputDigits == 0) {
    lcd.clear();
    lcd.print("Enter number");
    lcd.setCursor(0, 1);
    lcd.print("before SAVE");
    delay(1000);
    updateInputScreen();
    return;
  }

  cachedNumber = inputNumber;
  EEPROM.update(EEPROM_MAGIC_ADDR, EEPROM_MAGIC);
  EEPROM.put(EEPROM_VALUE_ADDR, cachedNumber);
  cacheValid = true;

  lcd.clear();
  lcd.print("CACHE SAVED");
  lcd.setCursor(0, 1);
  lcd.print("Value:");
  lcd.print(cachedNumber);
  delay(1200);

  clearInput();
  updateInputScreen();
}

void checkCache() {
  if (inputDigits == 0) {
    lcd.clear();
    lcd.print("Enter query");
    lcd.setCursor(0, 1);
    lcd.print("before CHECK");
    delay(1000);
    updateInputScreen();
    return;
  }

  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED, LOW);
  lcd.clear();

  if (cacheValid && inputNumber == cachedNumber) {
    digitalWrite(PIN_GREEN, HIGH);
    lcd.print("CACHE HIT!");
    lcd.setCursor(0, 1);
    lcd.print("Value:");
    lcd.print(inputNumber);
  } else {
    digitalWrite(PIN_RED, HIGH);
    lcd.print("CACHE MISS!");
    lcd.setCursor(0, 1);
    lcd.print("Value:");
    lcd.print(inputNumber);
  }

  delay(1600);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED, LOW);
  clearInput();
  updateInputScreen();
}

void setup() {
  for (byte i = 0; i < 4; i++) pinMode(buttons[i].pin, INPUT_PULLUP);

  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_RED, LOW);

  Wire.begin();
  lcd.init();
  lcd.backlight();

  if (EEPROM.read(EEPROM_MAGIC_ADDR) == EEPROM_MAGIC) {
    EEPROM.get(EEPROM_VALUE_ADDR, cachedNumber);
    cacheValid = (cachedNumber <= MAX_VALUE);
  }

  lcd.clear();
  lcd.print("CACHE PROTOTYPE");
  lcd.setCursor(0, 1);
  if (cacheValid) {
    lcd.print("Saved:");
    lcd.print(cachedNumber);
  } else {
    lcd.print("Cache: Empty");
  }
  delay(900);
  updateInputScreen();
}

void loop() {
  // Button 3: NEXT - cycle through digits 0 to 9.
  if (pressed(0)) {
    selectedDigit = (selectedDigit + 1) % 10;
    updateInputScreen();
  }

  // Button 1: CONFIRM - append the selected digit.
  if (pressed(1)) {
    if (inputNumber <= (MAX_VALUE - selectedDigit) / 10) {
      inputNumber = (inputNumber * 10) + selectedDigit;
      inputDigits++;
      updateInputScreen();
    } else {
      lcd.clear();
      lcd.print("Max 4 digits");
      delay(900);
      updateInputScreen();
    }
  }

  // Button 2: SAVE - store the entered number in EEPROM.
  if (pressed(2)) saveCache();

  // Button 4: CHECK - compare the query with the saved cache value.
  if (pressed(3)) checkCache();
}
