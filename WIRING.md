# RFID Attendance System - Wiring Diagram

## Component Overview

```
RC522 RFID Module (13.56 MHz) ──┐
                                 ├─→ Arduino UNO ──→ Computer (Serial)
16x2 I2C LCD Display ────────────┤
                                 ├─→ Breadboard
Green LED + Red LED + Buzzer ────┘
```

## RC522 RFID Module to Arduino (Direct Female-to-Male Wires)

| RC522 Pin | Arduino Pin | Color | Purpose |
|-----------|------------|-------|---------|
| VCC | 3.3V | Red | Power (⚠️ NEVER 5V) |
| GND | GND | Black | Ground |
| RST | Pin 9 | Orange | Reset |
| SDA (SS) | Pin 10 | Orange | Chip Select (SPI) |
| MOSI | Pin 11 | Orange | Master Out Slave In (SPI) |
| MISO | Pin 12 | Orange | Master In Slave Out (SPI) |
| SCK | Pin 13 | Orange | Serial Clock (SPI) |
| IRQ | Not Connected | - | Not used |

⚠️ **CRITICAL**: RC522 operates at 3.3V. Connecting to 5V will damage the module.

---

## 16x2 I2C LCD Display to Arduino (Direct Female-to-Male Wires)

| LCD Pin | Arduino Pin | Color | Purpose |
|---------|-----------|-------|---------|
| VCC | 5V | Red | Power |
| GND | GND | Black | Ground |
| SDA | A4 | Orange | I2C Data |
| SCL | A5 | Orange | I2C Clock |

I2C Address: **0x27** (configured in code)

---

## Breadboard Circuit (300-point with Power Rails)

### Power Distribution
```
Arduino 5V ──→ Breadboard + Rail
Arduino GND ──→ Breadboard − Rail
```

### Green LED (Pin 7)
```
Row 2:  LED long leg (anode) in col e
Row 3:  Empty row for spacing
Row 4:  LED short leg (cathode) in col e
        → 220Ω resistor from col e to col c
        → GND wire from col a to − rail
        → Signal wire from col d → Arduino Pin 7
```

### Red LED (Pin 6)
```
Row 6:  LED long leg (anode) in col e
Row 7:  Empty row for spacing
Row 8:  LED short leg (cathode) in col e
        → 220Ω resistor from col e to col c
        → GND wire from col a to − rail
        → Signal wire from col d → Arduino Pin 6
```

### Passive Buzzer (Pin 8)
```
Row 10: Buzzer positive (red) wire → col e
Row 11: Empty row for spacing
Row 12: Buzzer negative (black) wire → col e
        → GND wire from col a to − rail
        → Signal wire from col e → Arduino Pin 8
```

---

## Breadboard Layout Rules

- **Column e**: LED/component long legs and buzzer connections
- **Columns a–e**: Internally connected in the same row
- **Gap between e and f**: Electrical isolation
- **Col a GND**: All short leg (cathode) connections route here to − rail
- **Col d Signal**: All signal wires to Arduino route from here
- **Col b–c**: Resistor placement (one leg in each column)

---

## Pin Assignment Summary

| Arduino Pin | Component | Type | Direction |
|------------|-----------|------|-----------|
| 3.3V | RC522 VCC | Power | Output |
| 5V | LCD VCC | Power | Output |
| GND | All grounds | Ground | Return |
| Pin 6 | Red LED | Digital | Output |
| Pin 7 | Green LED | Digital | Output |
| Pin 8 | Passive Buzzer | Digital | Output |
| Pin 9 | RC522 RST | Digital | Output |
| Pin 10 | RC522 SDA (SS) | Digital | Output (SPI) |
| Pin 11 | RC522 MOSI | Digital | Output (SPI) |
| Pin 12 | RC522 MISO | Digital | Input (SPI) |
| Pin 13 | RC522 SCK | Digital | Output (SPI) |
| A4 | LCD SDA | Digital | Bidirectional (I2C) |
| A5 | LCD SCL | Digital | Bidirectional (I2C) |

---

## Communication Protocols

### SPI (RC522 to Arduino)
- **Clock Speed**: 10 MHz max
- **Pins Used**: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK)
- **Mode**: SPI_MODE0

### I2C (LCD to Arduino)
- **Clock Speed**: 100 kHz standard
- **Pins Used**: A4 (SDA), A5 (SCL)
- **Address**: 0x27

### Serial (Arduino to Computer)
- **Protocol**: UART
- **Baud Rate**: 9600
- **Connection**: USB Cable

---

## Component Specifications

| Component | Specs |
|-----------|-------|
| RC522 Module | 13.56 MHz, SPI, 3.3V supply |
| LCD Display | 16x2 character, I2C, 5V supply |
| Green LED | 2V forward voltage, 20mA max |
| Red LED | 2V forward voltage, 20mA max |
| Resistors | 220Ω (1/4W), carbon film |
| Passive Buzzer | 5V supply, frequency-based control |
| Breadboard | 300-point with power rails |

---

## Assembly Checklist

- [ ] RC522 module connected directly to Arduino pins (no breadboard)
- [ ] RC522 VCC on 3.3V pin (verified with multimeter)
- [ ] LCD connected directly to Arduino pins A4, A5 (no breadboard)
- [ ] LCD VCC on 5V via breadboard + rail
- [ ] Green LED in row 2, col e with proper spacing
- [ ] Red LED in row 6, col e with proper spacing
- [ ] Both LEDs have 220Ω resistors on short legs
- [ ] Buzzer connected to row 10, col e
- [ ] All GND connections routed through − rail
- [ ] Signal wires color-coded to Arduino pins
- [ ] USB cable connected for power and serial communication

---

## Common Mistakes to Avoid

❌ **Don't**: Connect RC522 VCC to 5V (will damage module)  
✅ **Do**: Connect RC522 VCC only to 3.3V

❌ **Don't**: Run Serial Monitor and Python script simultaneously  
✅ **Do**: Close Serial Monitor before running Python script

❌ **Don't**: Use an active buzzer (requires only ON/OFF)  
✅ **Do**: Use passive buzzer (requires frequency signal via tone())

❌ **Don't**: Place RC522 on breadboard  
✅ **Do**: Use female-to-male wires directly to Arduino

❌ **Don't**: Open Excel file while Python script is running  
✅ **Do**: Close Excel before running the script

---

## Troubleshooting

**RC522 not detected in code:**
- Check VCC is on 3.3V, not 5V
- Verify SPI pins (11, 12, 13) match Arduino connections
- Restart Arduino after checking connections

**LCD not displaying:**
- Verify I2C address is 0x27 (check with I2C scanner if needed)
- Check SDA/SCL connected to A4/A5
- Ensure LCD VCC is on 5V + rail

**LEDs not lighting:**
- Check resistors are 220Ω (use multimeter)
- Verify short legs (cathodes) are in correct rows
- Check signal wires are connected to correct pins (6 and 7)

**Buzzer not beeping:**
- Verify buzzer is passive (requires frequency control)
- Check positive wire is on Pin 8
- Ensure negative wire is on GND
