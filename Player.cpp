#include "Player.h"
#include<iostream>
#include "objPosArrayList.h"




Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();


    objPos headPos(mainGameMechsRef ->getBoardSizeX()/2,
                   mainGameMechsRef ->getBoardSizeY()/2,
                   '*' );


    playerPosList->insertHead(headPos);


}


Player::~Player()
{
    // delete any heap members here
    if (playerPosList) {
        delete playerPosList; // Free allocated memory
        playerPosList = nullptr;
    }
   
}


objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; // returning the reference to the player objPos array List


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
    objPos newHeadPos = playerPosList->getHeadElement();
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();
   
    switch(myDir) {
        case UP:
            newHeadPos.pos->y--;
            if (newHeadPos.pos->y <= 0) newHeadPos.pos->y = boardHeight - 2;
            break;
        case DOWN:
            newHeadPos.pos->y++;
            if (newHeadPos.pos->y >= boardHeight - 1) newHeadPos.pos->y = 1;
            break;
        case LEFT:
            newHeadPos.pos->x--;
            if (newHeadPos.pos->x <= 0) newHeadPos.pos->x = boardWidth - 2;
            break;
        case RIGHT:
            newHeadPos.pos->x++;
            if (newHeadPos.pos->x >= boardWidth - 1) newHeadPos.pos->x = 1;
            break;
    }




    //newHeadPos.symbol = '*';


    playerPosList->insertHead(newHeadPos);   //insert temporary obj pos to the head of the list
   
    playerPosList->removeTail();// later on for feature 2




}
