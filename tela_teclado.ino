
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);       

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();

  delay(1000);
}

void loop() {
  
  testscrolltext();
  
  delay(2);
}

const int linha1 = 30;
const int linha2 = 40;
const int linha3 = 50;

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.drawLine(0, linha1 -2, 128, linha1 -2, SSD1306_WHITE);
  
  display.setCursor(2, linha1);   display.print("q");
  display.drawLine(0, linha1 -2, 0, linha3 +8, SSD1306_WHITE);
  display.setCursor(10, linha1);   display.print("w");
  display.drawLine(8, linha1 -2, 8, linha3 +8, SSD1306_WHITE);
  display.setCursor(18, linha1);  display.print("e");
  display.drawLine(16, linha1 -2, 16, linha3 +8, SSD1306_WHITE);
  display.setCursor(26, linha1);  display.print("r");
  display.drawLine(24, linha1 -2, 24, linha3 +8, SSD1306_WHITE);
  display.setCursor(34, linha1);  display.print("t");
  display.drawLine(32, linha1 -2, 32, linha3 +8, SSD1306_WHITE);
  display.setCursor(42, linha1);  display.print("y");
  display.drawLine(40, linha1 -2, 40, linha3 +8, SSD1306_WHITE);
  display.setCursor(50, linha1);  display.print("u");
  display.drawLine(48, linha1 -2, 48, linha3 +8, SSD1306_WHITE);
  display.setCursor(58, linha1);  display.print("i");
  display.drawLine(56, linha1 -2, 56, linha3 +8, SSD1306_WHITE);
  display.setCursor(66, linha1);  display.print("o");
  display.drawLine(64, linha1 -2, 64, linha3 +8, SSD1306_WHITE);
  display.setCursor(74, linha1);  display.print("p");
  display.drawLine(72, linha1 -2, 72, linha3 +8, SSD1306_WHITE);
  display.drawLine(80, linha1 -2, 80, linha3 +8, SSD1306_WHITE);

  display.drawLine(0, linha2 -2, 128, linha2 -2, SSD1306_WHITE);
  
  display.setCursor(2, linha2);   display.print("a");
  display.setCursor(10, linha2);   display.print("s");
  display.setCursor(18, linha2);  display.print("d");
  display.setCursor(26, linha2);  display.print("f");
  display.setCursor(34, linha2);  display.print("g");
  display.setCursor(42, linha2);  display.print("h");
  display.setCursor(50, linha2);  display.print("j");
  display.setCursor(58, linha2);  display.print("k");
  display.setCursor(66, linha2);  display.print("l");

  display.drawLine(0, linha3 -2, 128, linha3 -2, SSD1306_WHITE);
   
  display.setCursor(2, linha3);   display.print("z");
  display.setCursor(10, linha3);   display.print("x");
  display.setCursor(18, linha3);  display.print("c");
  display.setCursor(26, linha3);  display.print("v");
  display.setCursor(34, linha3);  display.print("b");
  display.setCursor(42, linha3);  display.print("n");
  display.setCursor(50, linha3);  display.print("m");

  display.drawLine(0, linha3 +8, 128, linha3 +8, SSD1306_WHITE);




  display.display();      // Show initial text
  delay(100);
}
