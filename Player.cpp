#include "Player.h"
#include<iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.pos->x =mainGameMechsRef ->getBoardSizeX()/2;
    playerPos.pos->y =mainGameMechsRef ->getBoardSizeY()/2;
    playerPos.symbol='@';
    //playerPos.setObjPos(5, 5, '*');
}



Player::~Player()
{
    // delete any heap members here
    if (playerPos.pos) {
        delete playerPos.pos; // Free allocated memory
        playerPos.pos = nullptr;
    }
}

objPos Player::getPlayerPos() const
{
    return playerPos.getObjPos();
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef->getInput();
    
    switch(input) {
        case 'w': 
            if (myDir != DOWN) myDir = UP;
            break;
        case 's': 
            if (myDir != UP) myDir = DOWN;
            break;
        case 'a': 
            if (myDir != RIGHT) myDir = LEFT;
            break;
        case 'd': 
            if (myDir != LEFT) myDir = RIGHT;
            break;
    }
}

void Player::movePlayer() {

    //geetting current position
    int newX = playerPos.pos->x;
    int newY = playerPos.pos->y;
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();
    
    switch(myDir) {
        case UP:
            newY--;
            if (newY <= 0) newY = boardHeight - 2;
            break;
        case DOWN:
            newY++;
            if (newY >= boardHeight - 1) newY = 1;
            break;
        case LEFT:
            newX--;
            if (newX <= 0) newX = boardWidth - 2;
            break;
        case RIGHT:
            newX++;
            if (newX >= boardWidth - 1) newX = 1;
            break;
    }
    
    playerPos.setObjPos(newX, newY, '*');

}

