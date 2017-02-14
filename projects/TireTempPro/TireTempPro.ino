#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include "SplashScreen.h"

// display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// temp sensors
Adafruit_MLX90614 mlx_l = Adafruit_MLX90614(0x1B); // left
Adafruit_MLX90614 mlx_c = Adafruit_MLX90614(0x1C); // center
Adafruit_MLX90614 mlx_r = Adafruit_MLX90614(0x1D); // right

// draws splash screen on startup for two seconds
void drawSplashScreen() {
  display.clearDisplay();  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.println("TireTemp PRO");
  display.display();
  delay(100);
  display.drawBitmap(40, 5, splashScreen, 90, 30, WHITE);
  display.display();
  delay(2000);
}

// draws header text during runtime
void drawHeader() {
  display.setTextSize(1);
  display.setCursor(1,0);
  display.println("LEFT   CENTER   RIGHT");
}

// truncates double values
char* doubleToString(double value, int stringSize, int precision) {
  char charVal[10];
  dtostrf(value, stringSize, precision, charVal);
  return charVal;
}

// draws temperature values on OLED display
void drawTemp() {
  display.setTextSize(2);
  display.setCursor(1,12);

  char* tempLeft = doubleToString(mlx_l.readObjectTempC(), 2, 0);
  char* tempCenter = doubleToString(mlx_c.readObjectTempC(), 2, 0);
  char* tempRight = doubleToString(mlx_r.readObjectTempC(), 2, 0);

  display.print(tempLeft);
  display.print("  ");
  display.print(tempCenter);
  display.print("  ");
  display.println(tempRight);
}

void setup()   {       
  Serial.begin(9600);

  Serial.println("Begin mlx setup");
  mlx_l.begin(); 
  mlx_c.begin(); 
  mlx_r.begin(); 

  Serial.println("Begin display setup");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Serial.println("Draw splash screen");
  drawSplashScreen();
  
  Serial.println("Setup done!");
}

void loop() {
  display.clearDisplay();
  drawHeader();  
  drawTemp();
  display.display();
  delay(1000);
}

