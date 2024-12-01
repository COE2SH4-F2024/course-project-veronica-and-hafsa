#ifndef FOOD_H
#define FOOD_H

// Required header includes
#include "objPos.h"    //for objPos class to track food position
#include "GameMechs.h" //for board dimensions and game mechanics
#include <cstdlib>     //for rand() function in generating random positions
#include <time.h>     //for time() function to seed random generator

class Food {
    private:
        objPos foodPos; //stores position and symbol of the food
        GameMechs* mainGameMechsRef; //pointer to GameMechs for accessing board size
        objPosArrayList* foodBucket;

    public:
        Food(GameMechs* thisGMRef); //constructor: initializes food
        ~Food(); //destructor: cleans up any dynamically allocated memory
        
        //generates new food position
    void generateFood(objPosArrayList* blockOff);        
        //returns the current position of the food
        //const indicates this method won't modify class members
        objPos getFoodPos() const;
        
};

#endif