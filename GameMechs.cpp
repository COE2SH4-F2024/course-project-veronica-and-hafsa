#include "GameMechs.h"
#include <iostream>
#include "MacUILib.h"


GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false; //ensure this is set to false
    loseFlag = false;
    score = 0;
    boardSizeX = 30;  
    boardSizeY = 15;
}

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
GameMechs::~GameMechs()
{
    // no because you did not allocate anything t o the heap in the constructor

}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() 
{
    if (MacUILib_hasChar()){
        input=MacUILib_getChar();
    }
    
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


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