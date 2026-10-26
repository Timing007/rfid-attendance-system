# RFID-Based Attendance System

An automated attendance tracking system using Arduino UNO, RC522 RFID module, and Python-based Excel logging.

## Overview

This project demonstrates the design and implementation of an RFID-based attendance system that enables automated, contactless attendance tracking. When a registered RFID card is scanned, the system identifies the student, displays their information on an LCD screen, provides visual and auditory feedback via LEDs and a buzzer, and automatically logs the attendance to an Excel file.

## Features

- **Contactless Card Scanning**: Uses 13.56 MHz RFID cards for quick identification
- **Real-Time LCD Display**: Shows student name and ID number on a 16x2 I2C LCD
- **Visual & Auditory Feedback**: Green LED for success, red LED for access denied, passive buzzer for confirmation
- **Automatic Excel Logging**: Python script logs attendance with timestamp and date
- **Duplicate Prevention**: Detects and flags cards scanned multiple times in a session
- **Access Control**: Unregistered cards trigger access denied response

## Hardware Components

- Arduino UNO
- RC522 RFID Module (13.56 MHz)
- 16x2 I2C LCD Display
- RFID Cards (13.56 MHz, MIFARE format)
- Green LED and Red LED
- Passive Buzzer (5V)
- 220Ω Resistors (for LEDs)
- 300-point Breadboard
- Jumper Wires (male-to-male and female-to-male)
- USB Cable for Arduino

## Wiring Diagram

### RC522 to Arduino (Female-to-Male Wires)
- VCC → 3.3V
- GND → GND
- RST → Pin 9
- SDA (SS) → Pin 10
- MOSI → Pin 11
- MISO → Pin 12
- SCK → Pin 13

### LCD to Arduino
- VCC → 5V (via breadboard + rail)
- GND → GND
- SDA → A4
- SCL → A5

### LEDs and Buzzer (via Breadboard)
- Green LED → Pin 7
- Red LED → Pin 6
- Buzzer → Pin 8
- All grounds → GND rail

## Software Requirements

### Arduino
- Arduino IDE
- MFRC522 library (by GithubCommunity)
- LiquidCrystal_I2C library (by Frank de Brabander)

### Python
- Python 3.x
- pyserial: `pip install pyserial`
- openpyxl: `pip install openpyxl`

## Setup Instructions

### 1. Arduino Setup
1. Install Arduino IDE from arduino.cc
2. Install required libraries via Arduino IDE Library Manager
3. Update the `registeredUIDs` array with your RFID card UIDs
4. Update the `names` and `idNumbers` arrays with student information
5. Upload the sketch to Arduino UNO

### 2. Finding Your RFID Card UID
1. Upload the UID reading test code to Arduino
2. Open Serial Monitor (9600 baud)
3. Scan each card and note the UID displayed
4. Update the Arduino code with these UIDs

### 3. Python Setup
1. Install required libraries: `pip install pyserial openpyxl`
2. Update `PORT = "COM9"` to your Arduino's COM port (check in Device Manager)
3. Close Serial Monitor in Arduino IDE before running the script
4. Run: `python attendance.py`

## Operation

1. Power on the Arduino
2. System displays "Scan your card" on LCD
3. Student taps their RFID card
4. If registered: LCD shows welcome message + ID, green LED lights, beep sounds
5. If unregistered: LCD shows "Access Denied", red LED lights, long tone sounds
6. Attendance automatically logged to `attendance.xlsx` with timestamp

## Project Structure

```
rfid-attendance-system/
├── arduino/
│   └── rfid_attendance.ino
├── python/
│   └── attendance.py
├── docs/
│   ├── rfid_attendance_report.docx
│   └── WIRING.md
├── README.md
└── .gitignore
```

## Troubleshooting

**RC522 not detected:**
- Check that VCC is connected to 3.3V (not 5V)
- Verify SPI pins (11, 12, 13) are correct
- Try restarting Arduino

**Python script won't start:**
- Check COM port is correct
- Close Serial Monitor in Arduino IDE
- Ensure pyserial and openpyxl are installed

**Cards not scanning:**
- Verify card frequency is 13.56 MHz (MIFARE)
- Hold card within 5cm of RC522 module
- Check UID format in code matches scanned UIDs

**Excel file locked:**
- Close the Excel file before running Python script
- Avoid opening Excel while script is running

## Future Enhancements

- Wireless logging via ESP32 with Wi-Fi
- Cloud storage integration (Google Sheets, Firebase)
- Mobile app for remote attendance monitoring
- Multi-classroom support with centralized database
- QR code alternative alongside RFID

## Author

Akshat  Tiwari

## License

This project is open source and available under the MIT License.

## References

- Arduino Documentation: arduino.cc/en/Guide
- MFRC522 Library: github.com/miguelbalboa/rfid
- LiquidCrystal_I2C: github.com/johnrickman/LiquidCrystal_I2C
