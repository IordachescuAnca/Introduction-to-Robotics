#pragma once

#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcdInit();
void startMenu();
void menuOptions(int);
void setUp(int, bool);
void highScoreMenu(bool);
void lcdPlay(int, int);
void introduction();
