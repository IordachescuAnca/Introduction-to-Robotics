const int potPinGreen = A0;
const int potPinRed = A1;
const int potPinBlue = A2;

const int greenPin = 9;
const int redPin = 10;
const int bluePin = 11;

int potValueGreen = 0;
int ledValueGreen = 0;
int potValueRed = 0;
int ledValueRed = 0;
int potValueBlue = 0;
int ledValueBlue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValueGreen = analogRead(potPinGreen);
  ledValueGreen = map(potValueGreen, 0, 1023, 0, 255);
  
  potValueRed = analogRead(potPinRed);
  ledValueRed = map(potValueRed, 0, 1023, 0, 255);
  
  potValueBlue = analogRead(potPinBlue);
  ledValueBlue = map(potValueBlue, 0, 1023, 0, 255);
  
  setColor(ledValueGreen, ledValueRed, ledValueBlue);
}

void setColor(int green, int red, int blue){
  analogWrite(greenPin, green);
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
}
