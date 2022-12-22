#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>    
#include "printf.h"
#include "RF24.h"

RF24 radio(9, 10); //o pino 9 é conecado no CE, e o pino 10 no CSN
//#define RF_CE_PIN     9
//#define RF_CSN_PIN   10
//#define RF_MOSI_PIN  11
//#define RF_MISO_PIN  12
//#define RF_SCK_PIN   13

//

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);       

const int VRX = A0; 
const int VRY = A1; 
const int pinButton = A2;

uint8_t address[][6] = {"1Node", "2Node"};

bool radioNumber = 1; // aqui ele esta definindo a frequencia do radio

bool role = false;  

char mensagem[] = "1234567890123456789012345678901234567890"; // payload é praticamente o que ele vai escrever no radio ...quer jogar minecraft hoje a noite depois da chuva de meteoros que vai cair apos o eclipse lunar egipcico.
char letraRecebida;

int tamanho = sizeof(mensagem);

char texto[32] = "";
int posicaoDoTexto = 0;
bool capslockOn = false;

int X = 0;        
int Y = 0;
int button = 0;  

int tamX = 7;

const int linha1 = 36;
const int linha2 = 46;
const int linha3 = 56;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
  }

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }

  Serial.println(F("RF24/examples/GettingStarted"));

  Serial.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  while (!Serial.available()) {
    
  }
  char input = Serial.parseInt();
  radioNumber = input == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.setPALevel(RF24_PA_LOW);  

  radio.setPayloadSize(32); // aqui se eu não me engano ele esta vendo o tamanho da mensagem payload 

  radio.openWritingPipe(address[radioNumber]);    

  radio.openReadingPipe(1, address[!radioNumber]);
//     ↓ define o cargo (se ele esta trasmitindo ou recebendo)
  if (role) {
    radio.stopListening();  
  } else {
    radio.startListening(); 
  }
  
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

char mapaTeclado[2][3][16] = {{
  "QWERTYUIOP- +789",
  "ASDFGHJKL  ?!456",
  "ZXCVBNM    ,0123" 
},{
  "qwertyuiop- +789",
  "asdfghjkl  ?!456",
  "zxcvbnm    ,0123"
}};

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
  
  char letra = mapaTeclado[capslockOn][linha][coluna];

  Serial.print(" linha = ");
  Serial.print(linha);
  Serial.print(" coluna = ");
  Serial.print(coluna);
  Serial.print(" letra = ");
  Serial.println(letra);
  
  return mapaTeclado[capslockOn][linha][coluna];
}

void loop() {

  if (role) {

    unsigned long start_timer = micros();                  // começa o timer
    bool report = false;
    int i = 0;
    while (i<tamanho) {
      report = radio.write(&mensagem[i], sizeof(char));
      i = i + 1;
    }
    //bool report = radio.write(&payload, sizeof(payload));  //  transmite a mensagem
    unsigned long end_timer = micros();                    //  termina o timer              

    if (report) {
      Serial.print(F("Transmission successful! "));          
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);                 
      Serial.print(F(" us. Sent: "));
      Serial.println(mensagem);                               
      //payload += 0.01;                                       
    } else {
      Serial.println(F("Transmission failed or timed out")); 
    }

    delay(1000);  

  } else {
   

    uint8_t pipe;
    if (radio.available(&pipe)) {             
      radio.read(&letraRecebida, sizeof(char));            
      Serial.println(letraRecebida);                
    }
  } 

  if (Serial.available()) {
    

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {

      role = true;
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();

    } else if (c == 'R' && role) {
    

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();
    }
  }
  
  X = analogRead(VRX);
  Y = analogRead(VRY); 
  button = digitalRead(pinButton);

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

  if (X<400) {
    cursorX = constrain(cursorX + tamX + 1, 1, 121);
  }
  if (X>600) {
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
  
  display.setCursor(2, linha1); display.setTextColor(SSD1306_INVERSE);  display.print(capslockOn ? "q" : "Q");
  display.drawLine(0, linha1 -2, 0, linha3 +8, SSD1306_WHITE);
  display.setCursor(10, linha1);   display.print(capslockOn ? "w" : "W");
  display.drawLine(8, linha1 -2, 8, linha3 +8, SSD1306_WHITE);
  display.setCursor(18, linha1);  display.print(capslockOn ? "e" : "E");
  display.drawLine(16, linha1 -2, 16, linha3 +20, SSD1306_WHITE);
  display.setCursor(26, linha1);  display.print(capslockOn ? "r" : "R");
  display.drawLine(24, linha1 -2, 24, linha3 +8, SSD1306_WHITE);
  display.setCursor(34, linha1);  display.print(capslockOn ? "t" : "T");
  display.drawLine(32, linha1 -2, 32, linha3 +8, SSD1306_WHITE);
  display.setCursor(42, linha1);  display.print(capslockOn ? "y" : "Y");
  display.drawLine(40, linha1 -2, 40, linha3 +8, SSD1306_WHITE);
  display.setCursor(50, linha1);  display.print(capslockOn ? "u" : "U");
  display.drawLine(48, linha1 -2, 48, linha3 +8, SSD1306_WHITE);
  display.setCursor(58, linha1);  display.print(capslockOn ? "i" : "I");
  display.drawLine(56, linha1 -2, 56, linha3 +20, SSD1306_WHITE);
  display.setCursor(66, linha1);  display.print(capslockOn ? "o" : "O");
  display.drawLine(64, linha1 -2, 64, linha2 +8, SSD1306_WHITE);
  display.setCursor(74, linha1);  display.print(capslockOn ? "p" : "P");
  display.drawLine(72, linha1 -2, 72, linha2 +8, SSD1306_WHITE);
  display.drawLine(80, linha1 -2, 80, linha1 +8, SSD1306_WHITE);
  display.drawLine(96, linha1 -2, 96, linha3 +8, SSD1306_WHITE);
  display.drawLine(104, linha1 -2, 104, linha3 +8, SSD1306_WHITE);
  display.drawLine(112, linha1 -2, 112, linha3 +8, SSD1306_WHITE);
  display.drawLine(120, linha1 -2, 120, linha3 +8, SSD1306_WHITE);

  display.drawLine(0, linha2 -2, 128, linha2 -2, SSD1306_WHITE);
  
  display.setCursor(2, linha2);   display.print(capslockOn ? "a" : "A");
  display.setCursor(10, linha2);   display.print(capslockOn ? "s" : "S");
  display.setCursor(18, linha2);  display.print(capslockOn ? "d" : "D");
  display.setCursor(26, linha2);  display.print(capslockOn ? "f" : "F");
  display.setCursor(34, linha2);  display.print(capslockOn ? "g" : "G");
  display.setCursor(42, linha2);  display.print(capslockOn ? "h" : "H");
  display.setCursor(50, linha2);  display.print(capslockOn ? "j" : "J");
  display.setCursor(58, linha2);  display.print(capslockOn ? "k" : "K");
  display.setCursor(66, linha2);  display.print(capslockOn ? "l" : "L");

  display.drawLine(0, linha3 -2, 128, linha3 -2, SSD1306_WHITE);
   
  display.setCursor(2, linha3);   display.print(capslockOn ? "z" : "Z");
  display.setCursor(10, linha3);  display.print(capslockOn ? "x" : "X");
  display.setCursor(18, linha3);  display.print(capslockOn ? "c" : "C");
  display.setCursor(26, linha3);  display.print(capslockOn ? "v" : "V");
  display.setCursor(34, linha3);  display.print(capslockOn ? "b" : "B");
  display.setCursor(42, linha3);  display.print(capslockOn ? "n" : "N");
  display.setCursor(50, linha3);  display.print(capslockOn ? "m" : "M");
  
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
    //Serial.print("cursor = ");
    Serial.print(posicaoDoTexto);
    char letra = cursorXYParaLetra(cursorX, cursorY);
    if (letra == '-') {
      posicaoDoTexto = posicaoDoTexto - 1;
      texto[posicaoDoTexto] = '\0';
      Serial.println("BackSpace");
    } else if (letra== '+') {
      capslockOn = !capslockOn;
      Serial.println("CapsLock");
    } else {
      texto[posicaoDoTexto] = letra;
      posicaoDoTexto = posicaoDoTexto + 1;
    }
    Serial.println(texto);   
  }
    
  display.setCursor(1, 18); display.print(texto);

  display.display();      // Show initial text
}
