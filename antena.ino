#include <SPI.h>    
#include "printf.h"
#include "RF24.h"

RF24 radio(9, 10); //o pino 9 é conecado no CE, e o pino 10 no CSN
//#define RF_CE_PIN     9
//#define RF_CSN_PIN   10
//#define RF_MOSI_PIN  11
//#define RF_MISO_PIN  12
//#define RF_SCK_PIN   13

uint8_t address[][6] = {"1Node", "2Node"};

bool radioNumber = 1; // aqui ele esta definindo a frequencia do radio

bool role = false;  

char mensagem[] = "1234567890123456789012345678901234567890"; // payload é praticamente o que ele vai escrever no radio ...quer jogar minecraft hoje a noite depois da chuva de meteoros que vai cair apos o eclipse lunar egipcico.
char letraRecebida;

int tamanho = sizeof(mensagem);
void setup() {

  Serial.begin(115200);
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


  // printf_begin();             
  // radio.printDetails();       
  // radio.printPrettyDetails(); 

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
}
