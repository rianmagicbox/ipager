
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

const int linha1 = 36;
const int linha2 = 46;
const int linha3 = 56;

void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.drawLine(0, linha1 -2, 128, linha1 -2, SSD1306_WHITE);
  
  display.setCursor(2, linha1);   display.print("Q");
  display.drawLine(0, linha1 -2, 0, linha3 +8, SSD1306_WHITE);
  display.setCursor(10, linha1);   display.print("W");
  display.drawLine(8, linha1 -2, 8, linha3 +8, SSD1306_WHITE);
  display.setCursor(18, linha1);  display.print("E");
  display.drawLine(16, linha1 -2, 16, linha3 +20, SSD1306_WHITE);
  display.setCursor(26, linha1);  display.print("R");
  display.drawLine(24, linha1 -2, 24, linha3 +8, SSD1306_WHITE);
  display.setCursor(34, linha1);  display.print("T");
  display.drawLine(32, linha1 -2, 32, linha3 +8, SSD1306_WHITE);
  display.setCursor(42, linha1);  display.print("Y");
  display.drawLine(40, linha1 -2, 40, linha3 +8, SSD1306_WHITE);
  display.setCursor(50, linha1);  display.print("U");
  display.drawLine(48, linha1 -2, 48, linha3 +8, SSD1306_WHITE);
  display.setCursor(58, linha1);  display.print("I");
  display.drawLine(56, linha1 -2, 56, linha3 +20, SSD1306_WHITE);
  display.setCursor(66, linha1);  display.print("O");
  display.drawLine(64, linha1 -2, 64, linha2 +8, SSD1306_WHITE);
  display.setCursor(74, linha1);  display.print("P");
  display.drawLine(72, linha1 -2, 72, linha2 +8, SSD1306_WHITE);
  display.drawLine(80, linha1 -2, 80, linha1 +8, SSD1306_WHITE);
  display.drawLine(96, linha1 -2, 96, linha3 +8, SSD1306_WHITE);
  display.drawLine(104, linha1 -2, 104, linha3 +8, SSD1306_WHITE);
  display.drawLine(112, linha1 -2, 112, linha3 +8, SSD1306_WHITE);
  display.drawLine(120, linha1 -2, 120, linha3 +8, SSD1306_WHITE);

  display.drawLine(0, linha2 -2, 128, linha2 -2, SSD1306_WHITE);
  
  display.setCursor(2, linha2);   display.print("A");
  display.setCursor(10, linha2);   display.print("S");
  display.setCursor(18, linha2);  display.print("D");
  display.setCursor(26, linha2);  display.print("F");
  display.setCursor(34, linha2);  display.print("G");
  display.setCursor(42, linha2);  display.print("H");
  display.setCursor(50, linha2);  display.print("J");
  display.setCursor(58, linha2);  display.print("K");
  display.setCursor(66, linha2);  display.print("L");

  display.drawLine(0, linha3 -2, 128, linha3 -2, SSD1306_WHITE);
   
  display.setCursor(2, linha3);   display.print("Z");
  display.setCursor(10, linha3);  display.print("X");
  display.setCursor(18, linha3);  display.print("C");
  display.setCursor(26, linha3);  display.print("V");
  display.setCursor(34, linha3);  display.print("B");
  display.setCursor(42, linha3);  display.print("N");
  display.setCursor(50, linha3);  display.print("M");
  
  display.drawLine(0, linha3 +8, 128, linha3 +8, SSD1306_WHITE);

  display.setCursor(58, 56);  display.print("SPACE");
  display.setCursor(75, 46);  display.print("OK");
  display.setCursor(90, 46);  display.print("?");
  display.setCursor(90, 56);  display.print(",");
  display.setCursor(98, 46);  display.print("!");

  //numeros
  display.setCursor(98, linha3);  display.print("0");
  display.setCursor(106, linha3);  display.print("1");
  display.setCursor(114, linha3);  display.print("2");
  display.setCursor(122, linha3);  display.print("3");
  
  display.setCursor(106, linha2);  display.print("4");
  display.setCursor(114, linha2);  display.print("5");
  display.setCursor(122, linha2);  display.print("6");
  
  display.setCursor(106, linha1);  display.print("7");
  display.setCursor(114, linha1);  display.print("8");
  display.setCursor(122, linha1);  display.print("9");
  //numeros
  
  
  //del
  display.fillRect(83, 38, 12, 3, SSD1306_WHITE);
  display.drawLine(85, 36, 85, 42, SSD1306_WHITE);
  display.drawLine(84, 37, 84, 41, SSD1306_WHITE);
  display.drawLine(82, 39, 82, 39, SSD1306_WHITE);
  //del

  //casplock
  display.fillRect(99, 37, 3, 6, SSD1306_WHITE);
  display.drawLine(98, 38, 102, 38, SSD1306_WHITE);
  display.drawLine(100, 36, 100, 36, SSD1306_WHITE);
  //casplock
  
  display.drawLine(88, 44, 88, 64, SSD1306_WHITE);


  display.fillRect(0, 0, 128, 16, SSD1306_INVERSE);
  display.setTextColor(SSD1306_INVERSE);
  display.setCursor(1, 9); display.print("OLA AMIGO!!!");

  display.setCursor(1, 1); display.print("FULANO");

    display.setCursor(0, 18); display.print("M");
    display.setCursor(0, 26); display.print("M");

  display.display();      // Show initial text
  delay(100);
}
