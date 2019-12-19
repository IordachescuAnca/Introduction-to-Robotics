#include <EEPROM.h>

const int START_ADDRESS = 0;

int getScore(){
  int score = 0;
  for(int i = 0; i < sizeof(score); ++i){
      byte b = EEPROM.read(START_ADDRESS + i);
      score |= ((unsigned)b) << (i * 8);
  }
  if(score == -1) return 0;
  return score;
}

void setScore(int score){
 for (int i = 0; i < sizeof(score); ++i) {
      byte b = (score >> (i * 8)) & 0xFF;
      EEPROM.write(START_ADDRESS + i, b);
    }
}
