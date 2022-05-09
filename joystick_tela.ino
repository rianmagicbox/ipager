const int VRX = A0; 
const int VRY = A1; 
const int pinButton = A2;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int X = 0;        
int Y = 0;
int button = 0;        

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
  X = analogRead(VRX);
  Y = analogRead(VRY); 
  button = digitalRead(pinButton);

  Serial.print("X = ");
  Serial.print(X);
  Serial.print("\t Y = ");
  Serial.print(Y);
  Serial.print("\t button = ");
  Serial.println(button);
  
  testscrolltext();
  
  delay(2);
}

int fix = 33;
int randNumber = 33;

void testscrolltext(void) {
  display.clearDisplay();

  randNumber = random(33, 127);
  Serial.println(randNumber);

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  int XTela = map(X, 0, 1023, 0, 120);
  int YTela = map(Y, 0, 1023, 0, 56);
  display.setCursor(XTela, YTela);
  if (button == 1){
    display.write(fix);
  } else {
    display.write(randNumber);
    fix = randNumber;
  }
  display.display();      // Show initial text
  delay(100);
}
