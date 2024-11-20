#include "Player.h"
#include<iostream>


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; 
    myDir = STOP;                
    pos = new Pos{10, 5};        
    symbol = '*';                

    // Debug: Print initial position
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
    playerPosition.setObjPos(pos->x, pos->y, symbol); // Set the player's current position and symbol
    return playerPosition;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef->getInput(); // Get input from GameMechs

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
            break; // Ignore invalid inputs
    }

    // Debug: Output the current direction
    std::cout << "Direction updated: " << myDir << std::endl;
}

void Player::movePlayer() {
    // PPA3 Finite State Machine logic
    int boardWidth = mainGameMechsRef->getBoardSizeX();   // Get board width
    int boardHeight = mainGameMechsRef->getBoardSizeY();  // Get board height

    // Debug: Show current position before moving
    std::cout << "Before move: (" << pos->x << ", " << pos->y << ")" << std::endl;

    // Update position based on direction
    switch (myDir) {
        case UP:
            pos->y = (pos->y - 1 + boardHeight) % boardHeight; // Wrap around vertically
            break;
        case DOWN:
            pos->y = (pos->y + 1) % boardHeight;               // Wrap around vertically
            break;
        case LEFT:
            pos->x = (pos->x - 1 + boardWidth) % boardWidth;   // Wrap around horizontally
            break;
        case RIGHT:
            pos->x = (pos->x + 1) % boardWidth;                // Wrap around horizontally
            break;
        default:
            break; // No movement for STOP
    }

    // Debug: Show new position after moving
    std::cout << "After move: (" << pos->x << ", " << pos->y << ")" << std::endl;

}

// More methods to be added