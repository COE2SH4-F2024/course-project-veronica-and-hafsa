#include "Player.h"
#include<iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; 
    myDir = STOP;                
    pos = new Pos{10, 5};        
    symbol = '*';                

    std::cout << "Player initialized at position: (" //DEBUGGG
              << pos->x << ", " << pos->y << ")" 
              << std::endl;
    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete pos;
}

objPos Player::getPlayerPos() const
{
    objPos playerPosition;
    playerPosition.setObjPos(pos->x, pos->y, symbol); //Set the player's current position and symbol
    return playerPosition;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef->getInput(); 

    switch (input) {
        case 'w': case 'W':
            myDir = UP; 
            break;
        case 's': case 'S':
            myDir = DOWN; 
            break;
        case 'a': case 'A':
            myDir = LEFT; 
            break;
        case 'd': case 'D':
            myDir = RIGHT; 
            break;
        default:
            myDir = STOP; 
            break;
    }

    //DEBUGGG
    std::cout << "Direction updated: " << myDir << std::endl;
}

void Player::movePlayer() {
    // PPA3 Finite State Machine logic
    int boardWidth = mainGameMechsRef->getBoardSizeX();  
    int boardHeight = mainGameMechsRef->getBoardSizeY(); 

    
    std::cout << "Before move: (" << pos->x << ", " << pos->y << ")" << std::endl;//DEBUGG

    //updating position with wraparound logic
    switch (myDir) {
        case UP:
            pos->y = (pos->y - 1 + boardHeight) % boardHeight;
            break;
        case DOWN:
            pos->y = (pos->y + 1) % boardHeight;
            break;
        case LEFT:
            pos->x = (pos->x - 1 + boardWidth) % boardWidth;
            break;
        case RIGHT:
            pos->x = (pos->x + 1) % boardWidth;
            break;
        default:
            break;
    }

    
    std::cout << "After move: (" << pos->x << ", " << pos->y << ")" << std::endl;//DEBUGGG

}

// More methods to be added