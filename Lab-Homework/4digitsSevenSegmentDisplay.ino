const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;

const int pinDP = 4;

const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int pinSW = 1;
const int pinX = A0;
const int pinY = A1;

const int segSize = 8;
int segments[segSize] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

const int noOfDisplays = 4;
int digits[noOfDisplays] = {pinD1, pinD2, pinD3, pinD4};

const int hash[noOfDisplays+1] = {-1, 3, 1, 2, 0};
const int BLINK_SPEED = 500;

const int noOfDigits = 10;
byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1} // 9
};

int xValue = 0;
int yValue = 0;
int swValue = 0;
int lastSwValue = 0;

const int minValueY = 300;
const int maxValueY = 700;
int contorY = 1;
int joyMovedY = 0;

const int minValueX = 300;
const int maxValueX = 700;
int contorX = 0;
int joyMovedX = 0;

int isBlocked = 0;

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize-1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], decimalPoint);
}

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}


void setup(){
   pinMode(pinSW, INPUT_PULLUP);
   for (int i = 0; i < segSize; i++)
  {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop(){
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  swValue = digitalRead(pinSW);

  if (swValue != lastSwValue){
      if (swValue == LOW){
        isBlocked = 1-isBlocked;
      }
  }
  lastSwValue = swValue;
  //y control
  if (yValue < minValueY && joyMovedX == 0 && isBlocked == 0){
    if (contorY == 1){
      contorY = 4;
    }
    else {
      if (contorY > 1){
        contorY--;
      }
    }
    joyMovedX = 1;
  }
  if (yValue > maxValueY && joyMovedX == 0 && isBlocked == 0){
    if (contorY == 4){
      contorY = 1;
    }
    else{
      if (contorY < 4){
        contorY++;
      }
    }
    joyMovedX = 1;
  }
  if (minValueY <= yValue && yValue <= maxValueY){
    joyMovedX = 0;
  }

  //x control
  if (xValue < minValueX && joyMovedY == 0 && isBlocked == 1){
    if (contorX == 0){
      contorX = 9;
    }
    else {
      if (contorX > 0){
        contorX--;
      }
    }
    joyMovedY = 1;
  }
  if (xValue > maxValueX && joyMovedY == 0 && isBlocked == 1){
    if (contorX == 9){
      contorX = 0;
    }
    else {
      if (contorX < 9){
        contorX++;
      }
    }
    joyMovedY = 1;
  }
  if (minValueX <= xValue && xValue <= maxValueX){
    joyMovedY = 0;
  }

  showDigit(hash[contorY]);
  displayNumber(contorX, HIGH);
  
}
