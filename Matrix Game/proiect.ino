#include "joystick.h"
#include "lcd.h"
#include "highscore.h"
#include "matrix.h"
Joystick J;
Joystick moveBlocks;

int contorX = 1;
int contorY = 1;

bool setUpChoice = 1;

int getHighScore = 0;
int highScoreChoice = 1;

int flagStartGame = 0;
int interval = 1000;
int startGameTime = 0;
int previousStartGameTime = 0;

bool hasStarted = 0;
bool hasEnded = 0;

int line = 0;
int column = 0;
int rotation = 0;

int actualBlock = 0;
const int numberBlock = 4;
const int positionBlock = 5;
const int sizeMatr = 8;
int linesErased = 0;

int score = 0;
int lives = 3;

int firstScreenTime = 0;
int lastFirstScreenTime = 0;
int intervalScreen = 5000;
int flag = 0;
int flag1 = 0;

bool beginning = 1;

void setup(){
  lcdInit();
  lcInit();
  
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
}
void loop(){
  
 if(beginning){
  introduction();
  lcd.clear();
  beginning = 0;
 }
 J.readValues();
 J.checkMove();
 
 if (J.whichDisplay()){
    if (!(J.whichDisplay() == 2 && contorX == 1 && lives)){
      displaySmile();
    }
    if (J.whichDisplay() == 1){
       if(J.isLeft()){
        if (contorX > 1){
         contorX--;
        }
       }
     if (J.isRight()){
      if(contorX < 4){
        contorX++;
      }
     }
     menuOptions(contorX);
     if(J.clickedOn()) lcd.clear();
    }
    if (J.whichDisplay() == 2 && contorX == 2){
      setUpChoice = 1;
      if (J.isLeft()) setUpChoice = 1;
      if (J.isRight()) setUpChoice = 0;
      if (setUpChoice){
        if (J.isUp() && contorY < 3){
          contorY++;
          lcd.clear();
        }
        if (J.isDown() && contorY > 1){
          contorY--;
          lcd.clear();
        }
        setUp(contorY, setUpChoice);
      }
      else{
        setUp(contorY, setUpChoice);
        J.goBackMenu();
        lcd.clear();
      }
    } 
    
    i f(J.whichDisplay() == 1 && contorX == 4){
      J.goBackMenu();
      lcd.clear();
      contorX = 1;
    }
    if (J.whichDisplay() == 2 && contorX == 3){
      if (J.isRight()) highScoreChoice = 0;
      if (J.isLeft()) highScoreChoice = 1;
      highScoreMenu(highScoreChoice);
      if (J.isUp()){
        if (!highScoreChoice){
          J.goBackMenu();
          lcd.clear();
        }
        else{
          lcd.clear();
          setScore(0);
        }
      }
    }
    if (J.whichDisplay() == 2 && contorX == 1 && lives == 0){

      firstScreenTime = millis();
      if (flag == 0){
        lastFirstScreenTime = firstScreenTime;
        flag = 1;
      }
      if (firstScreenTime - lastFirstScreenTime >= intervalScreen){
        if (flag1 == 0){
          lcd.clear();
          flag1 = 1;
        }
        lcd.setCursor(0, 0);
        lcd.print("Choose L-go back");
        lcd.setCursor(0, 1);
        lcd.print("R-try again");
        if (J.isLeft()){
          lcd.clear();
          J.goBackMenu();
        }
        if (J.isRight()){
          lives = 3;
        }
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print("GameOver!");
        lcd.setCursor(0, 1);
        lcd.print("Your score:");
        lcd.print(score);
      }
    }
    else{
      flag = 0;
      flag1 = 0;
    }
    if (J.whichDisplay() == 2 && contorX == 1 && lives){
          startGameTime = millis();
          if (flagStartGame == 0){
            lcd.clear();
            previousStartGameTime = startGameTime;
            lcInit();
            flagStartGame = 1;
            lives = 3;
            score = 0;
          }
          lcdPlay(lives, score);
          
          if (startGameTime - previousStartGameTime >= interval/contorY){
            if (hasStarted == 0){
              linesErased = removeLines();
              if (linesErased){
                score += linesErased * sizeMatr * contorY;
                getHighScore = getScore();
                if (score > getHighScore){
                  setScore(score);
                }
              }
              line = 0;
              column = random() % positionBlock;
              actualBlock = random() % numberBlock;
              rotation = random() % numberBlock;
              if (checkDraw(actualBlock, line, column, rotation)){
                drawBlock(actualBlock, line, column, true, rotation);
              }
              else{
                lives--;
                resetMatrix();
                hasStarted = 0;
              }
              hasStarted = 1;
            }
            else{
              drawBlock(actualBlock, line, column, false, rotation);
              if (checkDraw(actualBlock, line+1, column, rotation)){
                line++;
              }
              else{
                hasStarted = 0;
              }
              drawBlock(actualBlock, line, column, true, rotation);
            }
            previousStartGameTime = startGameTime;
          }
    
          if (J.isRight()){
            drawBlock(actualBlock, line, column, false, rotation);
            if (column - 1 >= 0 && checkDraw(actualBlock, line, column-1, rotation)){
              column--;
            }
            drawBlock(actualBlock, line, column, true, rotation);
          }
    
          if (J.isLeft()){
            drawBlock(actualBlock, line, column, false, rotation);
            if (column + 1 < sizeMatr && checkDraw(actualBlock, line, column+1, rotation)){
              column++;
            }
            drawBlock(actualBlock, line, column, true, rotation);
          }
    
          if (J.isDown()){
            drawBlock(actualBlock, line, column, false, rotation);
            if(checkDraw(actualBlock, line+1, column, rotation)){
              line++;
            }
            else{
              hasStarted = 0;
            }
    
            drawBlock(actualBlock, line, column, true, rotation);
          }
          
          displayMatrix();
          Serial.println(score);
      }
    else{
      flagStartGame = 0;
    }
    
  }
   else{
    if (J.clickedOn()) lcd.clear();
    startMenu();
    displaySmile();
   }
}
