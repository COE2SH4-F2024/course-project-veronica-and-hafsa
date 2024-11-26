#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  //direction state

        Player(GameMechs* thisGMRef); //constructor
        ~Player(); //deconstructor

        objPosArrayList* getPlayerPos() const;; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

    private:
        objPosArrayList* playerPosList; // List to store player positions
        objPos initialpos;//initial position of player
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
        char symbol;
};




#endif