#include "joystick.h"

const int pinSW = 10;
const int pinX = A0;
const int pinY = A1;

const int minTreshold = 400;
const int maxTreshold = 700; 

Joystick::Joystick(){
  this->xValue = 0;
  this->yValue = 0;
  this->isMovedX = false;
  this->isMovedY = false;
  this->numberDisplay = 0;
  this->swState = false;
  this->lastSwState = false;
  pinMode(pinSW, INPUT_PULLUP);
}

void Joystick::readValues(){
  this->xValue = analogRead(pinX);
  this->yValue = analogRead(pinY);
  this->swState = digitalRead(pinSW);
}

bool Joystick::isRight(){
  if(this->xValue < minTreshold && !this->isMovedX){
    this->isMovedX = true;
    return true;
  }
  return false;
}

bool Joystick::isLeft(){
  if(this->xValue > maxTreshold && !this->isMovedX){
    this->isMovedX = true;
    return true;
  }
  return false;
}

bool Joystick::isDown(){
  if(this->yValue < minTreshold && !this->isMovedY){
    this->isMovedY = true;
    return true;
  }
  return false;
}

bool Joystick::isUp(){
  if(this->yValue > maxTreshold && !this->isMovedY){
    this->isMovedY = true;
    return true;
  }
  return false;
}

void Joystick::checkMove(){
  if(minTreshold <= this->xValue && this->xValue <= maxTreshold){
    this->isMovedX = false;
  }
  if(minTreshold <= this->yValue && this->yValue <= maxTreshold){
    this->isMovedY = false;
  }
}

int Joystick::whichDisplay(){
  return this->numberDisplay;
}

void Joystick::goBackMenu(){
  this->numberDisplay--;
}

bool Joystick::clickedOn(){
  bool itChanged = false;
  if(this->swState != this->lastSwState){
    if(this->swState == LOW){
      if(this->numberDisplay < 3){
      this->numberDisplay++;
      }
      itChanged = true;
    }
  }
  this->lastSwState = this->swState;
  
  return itChanged;
}
