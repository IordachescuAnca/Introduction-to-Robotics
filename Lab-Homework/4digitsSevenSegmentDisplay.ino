const uint8_t xPin = A0;
const uint8_t yPin = A1;
const uint8_t joyButton_pushPin = 1;
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


const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

int segments[segSize] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP };
int digits[noOfDisplays] = { pinD1, pinD2, pinD3, pinD4 };

byte digitMatrix[noOfDigits][segSize - 1] = {
//   a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int xValue = 0;
int yValue = 0;

int minLimitValue = 350;
int maxLimitValue = 700;
bool pushButtonValue;

bool isMoved = 0;
bool dpState = 0;

int joyButton_lastDebounce = 0;
bool joyButton_lastPushValue;
int joyButton_pushDebounceInterval = 20;

int currentDigitsValues[noOfDisplays] = { 0, 0, 0, 0 };

int currentDigit = 0;
int selectedDigit = noOfDisplays;
int digitToEdit = noOfDisplays - 1;


int flushInterval = 1;
int lastFlush = 0;


void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void displayDigit(int num, byte digit, byte decimalPoint) {
  showDigit(num);
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], decimalPoint);
}



void setup() {
  for (uint8_t i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (uint8_t i = 0; i < noOfDisplays; i++) {
    pinMode(digits[i], OUTPUT);
  }
   pinMode(joyButton_pushPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  if (selectedDigit == noOfDisplays)
  {
    //no digit is selected => blinking mode
    xValue = analogRead(xPin);
    if (xValue < minLimitValue && !isMoved)
    {
      //change digit to the left
      if (digitToEdit > 0)
        --digitToEdit;
      else
        digitToEdit = noOfDisplays - 1;
      isMoved = 1;
    }

    if (xValue > maxLimitValue&& !isMoved)
    {
      if (digitToEdit < noOfDisplays - 1)
        ++digitToEdit;
      else
        digitToEdit = 0;
      isMoved = 1;
    }

    if (xValue >= minLimitValue && xValue <= maxLimitValue)
      isMoved = 0;

    if (millis() - lastFlush >= flushInterval)
    {
      displayDigit(currentDigit, currentDigitsValues[currentDigit], false);
      lastFlush = millis();
      if (currentDigit == noOfDisplays - 1)
        currentDigit = 0;
      else
        ++currentDigit;
    }
  }
  else {
    yValue = analogRead(yPin);

    if (yValue < minLimitValue && !isMoved){
      if (currentDigitsValues[selectedDigit] >= 1){
        --currentDigitsValues[selectedDigit];
      }
      else{
        currentDigitsValues[selectedDigit] = noOfDigits - 1;
      }
      isMoved = 1;
    }

    if (yValue > maxLimitValue&& !isMoved)
    {
      if (currentDigitsValues[selectedDigit] < noOfDigits - 1){
        ++currentDigitsValues[selectedDigit];
      }
      else{
        currentDigitsValues[selectedDigit] = 0;
      }
      isMoved = 1;
    }

    if (yValue >= minLimitValue && yValue <= maxLimitValue){
      isMoved = 0;
    }

    if (millis() - lastFlush >= flushInterval){
      if (currentDigit == selectedDigit){
        displayDigit(currentDigit, currentDigitsValues[currentDigit], true);
      }
      else{
        displayDigit(currentDigit, currentDigitsValues[currentDigit], false);
      }

      lastFlush = millis();
      if (currentDigit + 1 == noOfDisplays)
        currentDigit = 0;
      else
        ++currentDigit;
    }
  }

  if(millis() - joyButton_lastDebounce >= joyButton_pushDebounceInterval)
  {
    joyButton_lastDebounce = millis();
    pushButtonValue = !digitalRead(joyButton_pushPin);

    if (pushButtonValue != joyButton_lastPushValue){
      if (pushButtonValue){
        Serial.println(pushButtonValue);
        if (selectedDigit == noOfDisplays){
          selectedDigit = digitToEdit;
          digitToEdit = noOfDisplays;
        }
        else{
          digitToEdit = selectedDigit;
          selectedDigit = noOfDisplays;
        }
      }
    joyButton_lastPushValue = pushButtonValue;
    }
  }
}
