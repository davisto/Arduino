#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "CityBitmap.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void drawBitmap() {
  display.clearDisplay();  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(28, 0);
  display.println("CODING NIGHT!");
  display.drawBitmap(13, 0, cityBitmap, 100, 30, WHITE);
  display.display();
}

void drawText() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(1,0);
  display.println("It's");
  
  display.setCursor(1,15);
  display.setTextSize(2);
  display.println("02:04 am.");
  display.display();
}

void setup()   {                
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  drawBitmap();
  delay(2000);
  
  drawText();
  delay(2000);
}

