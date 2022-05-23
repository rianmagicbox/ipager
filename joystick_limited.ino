const int VRX = A0; 
const int VRY = A1; 
const int pinButton = A2;

int X = 0;        
int Y = 0;
int button = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT_PULLUP);

  delay(1000);
}
int cursorX = 64;
int cursorY = 32;
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

  Serial.print(" cursorX = ");
  Serial.print(cursorX);
  Serial.print(" cursorY = ");
  Serial.println(cursorY);
  
  delay(100);

  if (X>600) {
    cursorX = constrain(cursorX + 1, 0, 128);
  }
  if (X<400) {
    cursorX = constrain(cursorX - 1, 0, 128);
  }
  if (Y>600) {
    cursorY = constrain(cursorY + 1, 0, 64);
  }
  if (Y<400) {
    cursorY = constrain(cursorY - 1, 0, 64);
  }
}
