#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SH1106 display(OLED_RESET);

const int touchPins[] = {2, 3, 4, 5};
const String password = "423123";
String input = "";
int ledCount = 0;

void setup() {
  Serial.begin(9600);
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  for (int i = 0; i < 4; i++) {
    pinMode(touchPins[i], INPUT);
  }
}

void loop() {

  for (int i = 0; i < 4; i++) {
    if (digitalRead(touchPins[i]) == HIGH) {

      input += String(i + 1);
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("SENHA");
      display.println(input);
      display.display();
      delay(300);
    }
  }
  
  if (input.length() == 6) {
    display.clearDisplay();
    display.setCursor(0, 0);
    if (input == password) {
      display.println("SENHA CORRETA");
    } else {
      display.println("SENHA INCORRETA");
    }
    display.display();
    
    input = "";
    delay(2000);
    display.clearDisplay();}}
