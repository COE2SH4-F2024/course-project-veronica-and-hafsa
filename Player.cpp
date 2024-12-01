#include "Player.h"
#include<iostream>
#include "objPosArrayList.h"
#include "MacUILib.h"
#include "Food.h"



 // Second body segment
   Player::Player(GameMechs *thisGMRef, Food* foodRef){
    mainGameMechsRef=thisGMRef;  
    food=foodRef;                 
    myDir=STOP;                  
    playerPosList=new objPosArrayList();  

    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    objPos headPos(startX, startY, '*');
    playerPosList->insertTail(headPos);
  
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
    objPos newHeadPos = playerPosList->getHeadElement();
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();
   
    bool consumed = false;

    switch(myDir) {
        case UP:
            newHeadPos.pos->y--;
            if (newHeadPos.pos->y == food->getFoodPos().pos->y &&
                newHeadPos.pos->x == food->getFoodPos().pos->x) {
                consumed = true; 
                food->generateFood(playerPosList);
                mainGameMechsRef->incrementScore();
                
            }
            if (newHeadPos.pos->y <= 0) newHeadPos.pos->y = boardHeight - 2;
            break;

        case DOWN:
            newHeadPos.pos->y++;
            if (newHeadPos.pos->y == food->getFoodPos().pos->y &&
                newHeadPos.pos->x == food->getFoodPos().pos->x) {
                consumed = true; 
                food->generateFood(playerPosList);
                mainGameMechsRef->incrementScore();
            }
            if (newHeadPos.pos->y >= boardHeight - 1) newHeadPos.pos->y = 1;
            break;

        case LEFT:
            newHeadPos.pos->x--;
            if (newHeadPos.pos->x == food->getFoodPos().pos->x &&
                newHeadPos.pos->y == food->getFoodPos().pos->y) {
                consumed = true; 
                food->generateFood(playerPosList);
                mainGameMechsRef->incrementScore();
            }
            if (newHeadPos.pos->x <= 0) newHeadPos.pos->x = boardWidth - 2;
            break;

        case RIGHT:
            newHeadPos.pos->x++;
            if (newHeadPos.pos->x == food->getFoodPos().pos->x &&
                newHeadPos.pos->y == food->getFoodPos().pos->y) {
                consumed = true; 
                food->generateFood(playerPosList);
                mainGameMechsRef->incrementScore();
            }
            if (newHeadPos.pos->x >= boardWidth - 1) newHeadPos.pos->x = 1;
            break;
    }

    playerPosList->insertHead(newHeadPos);

    if (!consumed) {
        playerPosList->removeTail(); 
    } 
}

bool Player::checkSelfCollision(){

    for(int i=1; i<playerPosList->getSize();i++)
    {
    
        objPos currentPos = playerPosList->getElement(i); 
        objPos headPos = playerPosList->getHeadElement();  

        if (currentPos.isPosEqual(&headPos))
        {
            mainGameMechsRef->setLoseFlag();
            return true;
        }

    }
    return false;
}

