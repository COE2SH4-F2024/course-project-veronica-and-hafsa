#include "Player.h"
#include<iostream>
#include "objPosArrayList.h"
#include "MacUILib.h"
#include "Food.h"



 //constructor for player class
 Player::Player(GameMechs *thisGMRef, Food* foodRef){
    mainGameMechsRef=thisGMRef;   //store reference to gameMech
    food=foodRef;                 //store reference to food object
    myDir=STOP;                  //initialize players direction as STOP
    playerPosList=new objPosArrayList();  //create new list to store players position

    //set the starting position of the player (center of board)
    int startX = mainGameMechsRef->getBoardSizeX() / 2;
    int startY = mainGameMechsRef->getBoardSizeY() / 2;

    //add the initial position head of the player to the list
    objPos headPos(startX, startY, '*');
    playerPosList->insertTail(headPos);
  
}


//deconstructor
Player::~Player()
{
    // delete any heap members here
    if (playerPosList) {
        delete playerPosList; // Free allocated memory
        playerPosList = nullptr;
    }
   
}

//return pointer to the players position list
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList; 
}

//update the players direction based on user input
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
    objPos newHeadPos = playerPosList->getHeadElement(); //get current head position
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();
   
    bool consumed = false; //tracks if food was consumed

    //update the players head position based on the direction
    switch(myDir) {
        case UP:
            newHeadPos.pos->y--;
            if (newHeadPos.pos->y == food->getFoodPos().pos->y &&
                newHeadPos.pos->x == food->getFoodPos().pos->x) {
                consumed = true; 
                food->generateFood(playerPosList); //generate new food
                mainGameMechsRef->incrementScore(); //increment the score
                
            }
            if (newHeadPos.pos->y <= 0) newHeadPos.pos->y = boardHeight - 2; //wrap around
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

    //add the new head position to the players position list
    playerPosList->insertHead(newHeadPos);

    //if food isnt consumed, remove tail to maintain the same length
    if (!consumed) {
        playerPosList->removeTail(); 
    } 
}

//check if player has collided
bool Player::checkSelfCollision(){

    for(int i=1; i<playerPosList->getSize();i++)
    {
    
        objPos currentPos = playerPosList->getElement(i); //get position of each body segment
        objPos headPos = playerPosList->getHeadElement();  //get the head position

        //if any segment matches the head, the player collides with itself
        if (currentPos.isPosEqual(&headPos))
        {
            mainGameMechsRef->setLoseFlag(); //set the game loss flag
            return true;
        }

    }
    return false; //no collision detected
}