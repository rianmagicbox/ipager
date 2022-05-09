const int VRX = A0; 
const int VRY = A1; 
const int pinButton = A2;

int X = 0;        
int Y = 0;
int button = 0;        

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT_PULLUP);
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

  delay(2);
}
