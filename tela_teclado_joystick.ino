#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);       

const int VRX = A0; 
const int VRY = A1; 
const int pinButton = A2;

char texto[32] = "marmelada";
int posicaoDoTexto = 0;

int X = 0;        
int Y = 0;
int button = 0;  

int tamX = 7;

const int linha1 = 36;
const int linha2 = 46;
const int linha3 = 56;

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

int cursorX = 1;
int cursorY = 35;

char mapaTeclado[3][16] = {
  "QWERTYUIOP   789",
  "ASDFGHJKL  ?!456",
  "ZXCVBNM ,0123" 
};

char cursorXYParaLetra (int X, int Y) {
  int linha;
  int coluna;
  if (Y == 35){
    linha = 0;  
  } else if (Y == 45){
    linha = 1;
  } else if (Y == 55){
    linha = 2;
  }

  coluna = X / 8;
  Serial.print("X = ");
  Serial.print(X);
  Serial.print("Y = ");
  Serial.print(Y);
  Serial.print("linha = ");
  Serial.print(linha);
  Serial.print("coluna = ");
  Serial.println(coluna);
  
  return mapaTeclado[linha][coluna];
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
  Serial.print(button);

  Serial.print(" cursorX = ");
  Serial.print(cursorX);
  Serial.print(" cursorY = ");
  Serial.println(cursorY);

  delay(100);
  //space
  if (cursorX >= 57 && cursorX <= 87 && cursorY == linha3 - 1) {
    tamX = 31;
    cursorX = 57;
    //ok
  } else if (cursorX >= 73 && cursorX <= 87 && cursorY == linha2 - 1) {
    tamX = 15;
    cursorX = 73;
    //backspace
  } else if (cursorX >= 81 && cursorX <= 95 && cursorY == linha1 - 1) {
    tamX = 15;
    cursorX = 81;
  } else { 
    tamX = 7;
  }

  if (X>600) {
    cursorX = constrain(cursorX + tamX + 1, 1, 121);
  }
  if (X<400) {
    cursorX = constrain(cursorX - 8, 1, 121);
  }
  if (Y>600) {
    cursorY = constrain(cursorY + 10, linha1, linha3 - 1);
  }
  if (Y<400) {
    cursorY = constrain(cursorY - 10, linha1 - 1, linha3);
  }
  
  testscrolltext();
  
  delay(2);
}



void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.drawLine(0, linha1 -2, 128, linha1 -2, SSD1306_WHITE);

  display.fillRect(cursorX, cursorY, tamX, 9, SSD1306_WHITE);
  
  display.setCursor(2, linha1); display.setTextColor(SSD1306_INVERSE);  display.print("Q");
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
  display.fillRect(86, 38, 9, 3, SSD1306_INVERSE);
  display.fillTriangle(82, 39, 85, 42, 85, 36, SSD1306_INVERSE);
  //del

  //casplock
  display.fillRect(99, 39, 3, 4, SSD1306_INVERSE);
  display.fillTriangle(98, 38, 102, 38, 100, 36, SSD1306_INVERSE);
  //casplock
  
  display.drawLine(88, 44, 88, 64, SSD1306_WHITE);


  display.fillRect(0, 0, 128, 16, SSD1306_INVERSE);
  display.setTextColor(SSD1306_INVERSE);
  display.setCursor(1, 9); display.print("OLA AMIGO!!!");

  display.setCursor(1, 1); display.print("FULANO");

  if (button == 0) {
    texto[posicaoDoTexto] = cursorXYParaLetra(cursorX, cursorY);
    posicaoDoTexto = posicaoDoTexto + 1;
  }

    display.setCursor(1, 18); display.print(texto);

  display.display();      // Show initial text
}
