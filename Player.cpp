#include "Player.h"
#include<iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; 
    myDir = STOP;                
    pos = new Pos{10, 5};                       
    symbol = '*';
    std::cout << "Player initialized at position: (" 
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
    playerPosition.setObjPos(pos->x, pos->y, symbol); // Set the current position and symbol
    return playerPosition;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef->getInput();

    switch (input) {
        case 'w': case 'W':
            if (myDir != DOWN) myDir = UP;
            break;
        case 's': case 'S':
            if (myDir != UP) myDir = DOWN;
            break;
        case 'a': case 'A':
            if (myDir != RIGHT) myDir = LEFT;
            break;
        case 'd': case 'D':
            if (myDir != LEFT) myDir = RIGHT;
            break;
        default:
            break; 
    }
    std::cout << "Direction updated to: " << myDir << std::endl;
}

void Player::movePlayer() {
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();

    //DEBUGG
    std::cout << "Before move: (" << pos->x << ", " << pos->y << "), Direction: " << myDir << std::endl;

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

    //DEBUGG
    std::cout << "After move: (" << pos->x << ", " << pos->y << ")" << std::endl;

}

// More methods to be added