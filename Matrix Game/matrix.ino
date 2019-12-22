#include "matrix.h"

const int pinDin = 9;
const int pinClk = 8;
const int pinLoad = 7;
const int noDriver = 1;

LedControl lc = LedControl(pinDin, pinClk, pinLoad, noDriver);

void lcInit(){
  lc.shutdown(0, false); 
  lc.setIntensity(0, 2); 
  lc.clearDisplay(0);
}

const int sizeMatrix = 8;

bool smileyMatrix[sizeMatrix][sizeMatrix] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 1, 0},
{0, 0, 1, 1, 1, 1, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

void displaySmile(){
  for (int row = 0; row < sizeMatrix; row++){
    for (int col = 0; col < sizeMatrix; col++){
      lc.setLed(0, row, col, smileyMatrix[row][col]);
    }
  }
}

bool gameMatrix[sizeMatrix][sizeMatrix] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

void resetMatrix(){
  for (int row = 0; row < sizeMatrix; row++){
    for (int col = 0; col < sizeMatrix; col++){
      gameMatrix[row][col] = 0;
    }
  }
}

void displayMatrix(){
  for (int row = 0; row < sizeMatrix; row++){
    for (int col = 0; col < sizeMatrix; col++){
      lc.setLed(0, row, col, gameMatrix[row][col]);
    }
  }
}

void drawSquare(int row, int column, bool choice){
  gameMatrix[row][column] = choice;
  gameMatrix[row][column + 1] = choice;
  gameMatrix[row + 1][column] = choice;
  gameMatrix[row + 1][column + 1] = choice;
    
}
bool checkDrawSquare(int row, int column){
  if (gameMatrix[row][column] || gameMatrix[row + 1][column] || gameMatrix[row][column + 1] || gameMatrix[row + 1][column + 1]) return 0;
  if (row + 1 >= sizeMatrix) return 0;
  if (column < 0 || column + 1 >= sizeMatrix) return 0;

  return 1;
}

void drawTshaped(int row, int column, bool choice, int rotation){
  if (rotation == 0){
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row + 1][column + 1] = choice;
    gameMatrix[row + 1][column + 2] = choice;
  }
  if (rotation == 1){
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row + 1][column + 1] = choice;
    gameMatrix[row + 2][column + 1] = choice;
  }
  if (rotation == 2){
    gameMatrix[row][column] = choice;
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row][column + 2] = choice;
    gameMatrix[row + 1][column + 1] = choice;
  }
  if (rotation == 3){
    gameMatrix[row][column] = choice;
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row + 2][column] = choice;
    gameMatrix[row + 1][column + 1] = choice;
  }
}

bool checkDrawTshaped(int row, int column, int rotation){
  if (rotation == 0){
    if (gameMatrix[row][column + 1] || gameMatrix[row + 1][column] || gameMatrix[row + 1][column + 1] || gameMatrix[row + 1][column + 2]) return 0;
    if (row + 1 >= sizeMatrix) return 0;
    if (column < 0 || column + 2 >= sizeMatrix) return 0;
    
    return 1;
  }
  if (rotation == 1){
    if (gameMatrix[row + 1][column] || gameMatrix[row][column + 1] || gameMatrix[row + 1][column + 1] || gameMatrix[row + 2][column + 1]) return 0;
    if (row + 2 >= sizeMatrix) return 0;
    if (column < 0 || column + 1 >= sizeMatrix) return 0;
    
    return 1;
  }

  if (rotation == 2){
    if (gameMatrix[row][column] || gameMatrix[row][column + 1] || gameMatrix[row][column + 2] || gameMatrix[row + 1][column + 1]) return 0;
    if (row + 1 >= sizeMatrix) return 0;
    if (column < 0 || column + 2 >= sizeMatrix) return 0;
    
    return 1;
  }
  if (rotation == 3){
    if (gameMatrix[row][column] || gameMatrix[row + 1][column] || gameMatrix[row + 2][column] || gameMatrix[row + 1][column + 1]) return 0;
    if (row + 2 >= sizeMatrix) return 0;
    if (column < 0 || column + 1 >= sizeMatrix) return 0;
    
    return 1;
  }
}

void drawSshaped(int row, int column, bool choice, int rotation){

  if (rotation == 0){
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row][column + 2] = choice;
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row + 1][column + 1] = choice;
  }
  if (rotation == 1){
    gameMatrix[row][column] = choice;
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row + 1][column + 1] = choice;
    gameMatrix[row + 2][column + 1] = choice;
  }
  if (rotation == 2){
    gameMatrix[row][column] = choice;
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row + 1][column + 1] = choice;
    gameMatrix[row + 1][column + 2] = choice;
  }
  if (rotation == 3){
    gameMatrix[row][column + 1] = choice;
    gameMatrix[row + 1][column] = choice;
    gameMatrix[row + 1][column + 1] = choice;
    gameMatrix[row + 2][column] = choice;
  }
}

bool checkDrawSshaped(int row, int column, int rotation){
  if (rotation == 0){
    if (gameMatrix[row][column + 1] || gameMatrix[row][column + 2] || gameMatrix[row + 1][column] || gameMatrix[row + 1][column + 1]) return 0;
    if (row + 1 >= sizeMatrix) return 0;
    if (column < 0 || column + 2 >= sizeMatrix) return 0;
    
    return 1;
  }

  if (rotation == 1){
    if (gameMatrix[row][column] || gameMatrix[row + 1][column] || gameMatrix[row + 1][column + 1] || gameMatrix[row + 2][column + 1]) return 0;
    if (row + 2 >= sizeMatrix) return 0;
    if (column < 0 || column + 1 >= sizeMatrix) return 0;
    
    return 1;
  }

  if (rotation == 2){
    if (gameMatrix[row][column] || gameMatrix[row][column + 1] || gameMatrix[row + 1][column + 1] || gameMatrix[row + 1][column + 2]) return 0;
    if (row + 1 >= sizeMatrix) return 0;
    if (column < 0 || column + 2 >= sizeMatrix) return 0;
    
    return 1;
  }

  if (rotation == 3){
    if (gameMatrix[row][column + 1] || gameMatrix[row + 1][column] || gameMatrix[row + 1][column + 1] || gameMatrix[row + 2][column]) return 0;
    if (row + 2 >= sizeMatrix) return 0;
    if (column < 0 || column + 1 >= sizeMatrix) return 0;
    
    return 1;
  }
  
}


void drawIshaped(int row, int column, bool choice){
  gameMatrix[row][column] = choice;
  gameMatrix[row + 1][column] = choice;
  gameMatrix[row + 2][column] = choice;
  gameMatrix[row + 3][column] = choice;
}

bool checkDrawIshaped(int row, int column){
  if (gameMatrix[row][column] || gameMatrix[row + 1][column] || gameMatrix[row + 2][column] || gameMatrix[row + 3][column]) return 0;
  if (row + 3 >= sizeMatrix) return 0;
  if (column < 0 || column >= sizeMatrix) return 0;
  
  return 1;
}

void drawBlock(int numberBlock, int row, int column, bool choice, int rotation){
  if (numberBlock == 0){
    drawSquare(row, column, choice);
  }
  if (numberBlock == 1){
    drawTshaped(row, column, choice, rotation);
  }
  if (numberBlock == 2){
    drawSshaped(row, column, choice, rotation);
  }
  if (numberBlock == 3){
    drawIshaped(row, column, choice);
  }
}

bool checkDraw(int numberBlock, int row, int column, int rotation){
  if (numberBlock == 0){
    return checkDrawSquare(row, column);
  }
  if (numberBlock == 1){
    return checkDrawTshaped(row, column, rotation);
  }
  if (numberBlock == 2){
    return checkDrawSshaped(row, column, rotation);
  }
  if (numberBlock == 3){
    return checkDrawIshaped(row, column);
  }
}

bool auxMatrix[sizeMatrix][sizeMatrix] = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

void copyMatrix(){
  for (int row = 0; row < sizeMatrix; row++){
    for (int col = 0; col < sizeMatrix; col++){
      auxMatrix[row][col] = gameMatrix[row][col];
    }
  }
}

int removeLines(){
  int contor = 0;
  for (int row = 0; row < sizeMatrix; row++){
    bool full = 1;
    for (int col = 0; col < sizeMatrix; col++){
      if (gameMatrix[row][col] == 0){
        full = 0;
        break;
      }
    }
    if (full){
      contor++;
      copyMatrix();
      for (int newCol = 0; newCol < sizeMatrix; newCol++){
        gameMatrix[0][newCol] = 0;
      }
      for (int newRow = 1; newRow <= row; newRow++){
        for (int newCol = 0; newCol < sizeMatrix; newCol++){
          gameMatrix[newRow][newCol] = auxMatrix[newRow-1][newCol];
        }
      }
    }
  }
  return contor;
}
