#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9
#define GREEN_LED_PIN 4
#define RED_LED_PIN 5
#define LCD_I2C_ADDRESS 0x3F
#define LCD_COLUMNS 16
#define LCD_ROWS 2

MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN);
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

const String authorizedUIDs[] = {"A3 7B FB 1A"};

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
  
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
  
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Scan Card...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    String content = readCardUID();

    if (isAuthorized(content)) {
        handleAccess(true);
    } else {
        handleAccess(false);
    }
}

String readCardUID() {
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        content += (mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ") + String(mfrc522.uid.uidByte[i], HEX);
    }
    return content.toUpperCase();
}

bool isAuthorized(const String &content) {
    for (const String &uid : authorizedUIDs) {
        if (content.substring(1) == uid) {
            return true;
        }
    }
    return false;
}

void handleAccess(bool authorized) {
    if (authorized) {
        digitalWrite(GREEN_LED_PIN, HIGH);
        Serial.println("Authorized access");
        lcd.clear();
        lcd.print("Acesso Permitido");
        delay(3000);
        digitalWrite(GREEN_LED_PIN, LOW);
    } else {
        digitalWrite(RED_LED_PIN, HIGH);
        Serial.println("Access denied");
        lcd.clear();
        lcd.print("Acesso Negado");
        delay(3000);
        digitalWrite(RED_LED_PIN, LOW);
    }
}
