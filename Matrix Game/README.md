***Matrix Game***

[Video](https://www.youtube.com/watch?v=tUaifLaPN-A&t=6s) 

The Matrix Game that I implemented is called Tetris.

**Description of the project**: The purpose of the game is destroying lines of block before it reaches the top. There are four-connected blocks that will fall down and the player has to choose the rotation that create lines that fill the box horizontally, this will clear the lines of blocks.


**Hardware**:

- Game menu is displayed on an *LCD display*.
- The game is displayed on an *8x8 LED Matrix* driven by *MAX7219 driver*.
- The *joystick* is used for navigating in the game menu and to move left, right and down during the game.

**About the game**:
- Score: Every time a line of blockes is cleared, the score increases by 8(numbers of blockes that are on a line) multiplied by the level the player has reached.
- Levels : The game it has 3 levels: easy, medium and hard. It can be changed in SetUp.
- Progress: is represented by speed. From the easy level to hard level it will increase the speed. In this way, the herd level will be 3 times faster than the first one and the medium level will be 2 times faster than the first one.
- Lives: The player has 3 lives. It has the chance to play the game without resetting the score until it loses all his lives. When it loses all his chances, the player is asked if it wants to play again or to go back to the game menu.
- HighScore: The highscore and the player that reached the highscore will be kept in memory(*EEPROM*). The HighScore can be reset.

PS: While you are navigating through game menu, a smiley face is displayed. :)
