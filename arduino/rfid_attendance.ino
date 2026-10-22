#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define GREEN_LED 7
#define RED_LED 6
#define BUZZER 8

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

byte registeredUIDs[3][4] = {
  {0x56, 0xF3, 0x91, 0x26}, // Akshat
  {0xF6, 0xF6, 0x9D, 0x26}, // Arnav
  {0x66, 0x57, 0x0C, 0x26}  // Akash
};

String names[3]     = {"Akshat", "Arnav", "Akash"};
String idNumbers[3] = {"4872519", "3916204", "7253981"};
bool attended[3]    = {false, false, false};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Attendance");
  lcd.setCursor(0, 1);
  lcd.print("System Ready!");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");

  Serial.println("=== Attendance System Ready ===");
}

int getStudentIndex(byte *uid) {
  for (int i = 0; i < 3; i++) {
    bool match = true;
    for (int j = 0; j < 4; j++) {
      if (uid[j] != registeredUIDs[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return i;
  }
  return -1;
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  int index = getStudentIndex(rfid.uid.uidByte);

  lcd.clear();

  if (index != -1) {
    if (!attended[index]) {
      attended[index] = true;

      lcd.setCursor(0, 0);
      lcd.print("Hi " + names[index] + "!");
      lcd.setCursor(0, 1);
      lcd.print("ID: " + idNumbers[index]);

      digitalWrite(GREEN_LED, HIGH);
      tone(BUZZER, 1000);
      delay(300);
      noTone(BUZZER);
      delay(700);
      digitalWrite(GREEN_LED, LOW);

      Serial.print("PRESENT: ");
      Serial.println(names[index]);

    } else {
      lcd.setCursor(0, 0);
      lcd.print("Hi " + names[index] + "!");
      lcd.setCursor(0, 1);
      lcd.print("Already marked!");

      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      tone(BUZZER, 500);
      delay(500);
      noTone(BUZZER);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);

      Serial.print("ALREADY MARKED: ");
      Serial.println(names[index]);
    }

  } else {
    lcd.setCursor(0, 0);
    lcd.print("Access Denied!");
    lcd.setCursor(0, 1);
    lcd.print("Unknown card");

    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    noTone(BUZZER);
    digitalWrite(RED_LED, LOW);

    Serial.println("DENIED: Unknown card");
  }

  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");

  Serial.println("--- Attendance Log ---");
  for (int i = 0; i < 3; i++) {
    Serial.print(names[i]);
    Serial.print(" (");
    Serial.print(idNumbers[i]);
    Serial.print("): ");
    Serial.println(attended[i] ? "Present" : "Absent");
  }
  Serial.println("----------------------");

  rfid.PICC_HaltA();
}
