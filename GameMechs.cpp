#include "GameMechs.h"
#include <iostream>
#include "MacUILib.h"


GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false; 
    loseFlag = false; 
    score = 0; //starts with 0 score
    boardSizeX = 30;  //board width
    boardSizeY = 15;  //board height
}

//constructor which allows specifying board diemesions
GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs() //deconsturctor
{
    // no because you did not allocate anything to the heap in the constructor

}

//game state checkin methods
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; //retrun exit status
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; //return loss status
}
    
//inputs hnadling methods
char GameMechs::getInput() 
{
    if (MacUILib_hasChar()){
        input=MacUILib_getChar(); //get character if availible
    }
    
    return input;
}

//score
int GameMechs::getScore() const
{
    return score; //return score
}

void GameMechs::incrementScore()
{
    score++; //increment score by one
}

//board dimesions
int GameMechs::getBoardSizeX() const
{
    return boardSizeX; //return board width
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; //return board height
}

//game state modifications
void GameMechs::setExitTrue()
{
    std::cout << "Exit flag set to true.\n";
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    std::cout << "Lose flag set to true.\n";
    loseFlag = true;
}


void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
   input = 0;
}

// More methods should be added here