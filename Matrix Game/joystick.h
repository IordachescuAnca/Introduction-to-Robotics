#pragma once

class Joystick{
  private:
  int xValue;
  int yValue;
  bool isMovedX;
  bool isMovedY;
  int numberDisplay;
  bool swState;
  bool lastSwState;
  public:
  Joystick();
  void readValues();
  bool isLeft();
  bool isRight();
  bool isUp();
  bool isDown();
  bool isPushed();
  int whichDisplay();
  void checkMove();
  void goBackMenu();
  bool clickedOn();
};
