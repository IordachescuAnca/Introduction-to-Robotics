#include <LiquidCrystal.h>
#include <EEPROM.h>
const int START_ADDRESS = 0;

const int pinSW = 10;
const int pinY = A1;
const int pinX = A0;

const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);


const int minValue = 400;
const int maxValue = 600;
int isMoved = 0;
int contor = 1;
int yValue = 0;

int buttonState = 0;
int lastButtonState = 0;
int clickedOn = 0;
int flag = 0;

int contorLevel = 0;
int xValue = 0;
int isMovedigit = 0;

char namePlayer[10];
int index = 0;
char inChar = -1;

int score = 0;
int flagScore = 0;
int startGameTime = 0;
int previousStartGameTime = 0;
int interval = 5000;
int highScore = 0;

void displayMenu(int contor){
    if(contor == 1){
    lcd.setCursor(0,0);
    lcd.print(">Start    Setup ");
    lcd.setCursor(0,1);
    lcd.print(" high Score");
  }
  else if(contor == 2){
    lcd.setCursor(0,0);
    lcd.print(" Start   >Setup");
    lcd.setCursor(0,1);
    lcd.print(" high Score");
  }
  else if(contor == 3){
    lcd.setCursor(0,0);
    lcd.print(" Start    Setup");
    lcd.setCursor(0,1);
    lcd.print(">high Score");
  }
}

int getScore(){
  int score = 0;
  for(int i = 0; i < sizeof(score); ++i){
      byte b = EEPROM.read(START_ADDRESS + i);
      score |= ((unsigned)b) << (i * 8);
  }
  return score;
}

void setScore(int score){
 for (int i = 0; i < sizeof(score); ++i) {
      byte b = (score >> (i * 8)) & 0xFF;
      EEPROM.write(START_ADDRESS + i, b);
    }
}

void setup() {  
pinMode(pinSW, INPUT_PULLUP);

lcd.begin(16, 2);
lcd.print(">Start  Setup");
lcd.setCursor(0,1);
lcd.print("highScore");
Serial.begin(9600);

}


void loop() {
  yValue = analogRead(pinY);
  buttonState = digitalRead(pinSW);
  if(!clickedOn){
    flagScore = 0;
    displayMenu(contor);

    if(yValue < minValue && isMoved == 0){
      if(contor > 1){
        contor--;
      }
      isMoved = 1;
    }
    if(yValue > maxValue && isMoved == 0){
      if(contor < 3){
        contor++;
      }
      isMoved = 1;
    }
    if(minValue <= yValue && yValue <= maxValue){
      isMoved  = 0;
    }
  }

  if(buttonState != lastButtonState){
    if(buttonState == LOW){
      clickedOn = !clickedOn;
      if(clickedOn == 0){
        flag = 0;
      }
    }
  }
  lastButtonState = buttonState;

  if(clickedOn){
    if(flag == 0){
      lcd.clear();
      flag = 1;
    }
    if(contor == 1){
      startGameTime = millis();
      if(flagScore == 0){
        previousStartGameTime = startGameTime;
        flagScore = 1;
      }
      if(startGameTime - previousStartGameTime >= interval){
        contorLevel++;
        previousStartGameTime = startGameTime;
      }
      
      lcd.setCursor(0, 0);
      lcd.print("Lives:3");
      lcd.print(" Level:");
      lcd.print(contorLevel);
      lcd.setCursor(0,1);
      score = 3 * contorLevel;
      lcd.print("Score:");
      lcd.print(score);
      highScore = getScore();
      if(score > highScore){
        setScore(score);
      }
    }
    if(contor == 2){
      xValue = analogRead(pinX);
      if(xValue < minValue && isMovedigit == 0){
        if(contorLevel > 0){
          contorLevel--;
        }
        isMovedigit = 1;
      }
      if(xValue > maxValue && isMovedigit == 0){
        if(contorLevel < 50){
          contorLevel++;
        }
        isMovedigit = 1;
      }
      if(minValue <= xValue && xValue <= maxValue){
        isMovedigit  = 0;
      }

      while (Serial.available() > 0){
        if(index < 10){
            inChar = Serial.read(); 
            namePlayer[index] = inChar;
            index++;
            namePlayer[index] = '\0';
        }
      }
      namePlayer[index-1] = '\0';
      //namePlayer = Serial.readString();
      
      lcd.setCursor(0,0);
      lcd.print("Level: ");
      lcd.print(contorLevel);
      lcd.setCursor(0,1);
      lcd.print("Player:");
      lcd.print(namePlayer);
    }
    if(contor == 3){
      lcd.setCursor(0,0);
      lcd.print("HighScore: ");
      highScore = getScore();
      if(highScore == -1){
        highScore = 0;
      }
      lcd.print(highScore);
    }
  }

}
