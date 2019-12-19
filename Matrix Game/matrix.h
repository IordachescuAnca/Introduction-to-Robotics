#pragma once
#include "LedControl.h"

extern LedControl lc;

void lcInit();
void displaySmile();
void resetMatrix();
void drawSquare(int, int, bool);
bool checkDrawSquare(int, int);
void drawTshaped(int, int, bool, int);
bool checkDrawTshaped(int, int, int);
void drawSshaped(int, int, bool, int);
bool checkDrawSshaped(int, int, int);
void drawIshaped(int, int, bool);
bool checkDrawIshaped(int, int);
void drawBlock(int, int, int, bool, int);
bool checkDraw(int, int, int, int);
void copyMatrix();
int removeLines();
