#include "Food.h"
#include "MacUILib.h"


//constructor: initlaizes food object with game mechanics
Food::Food(GameMechs* thisGMRef) 
{
    mainGameMechsRef = thisGMRef; //stores reference to game mechs
    foodPos.pos = new Pos;//allocate memory for food position
    foodPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;;  //start with a fixed position
    foodPos.pos->y = mainGameMechsRef->getBoardSizeY() / 3;;  //different from player start
    foodPos.symbol = 'o';
    
    //random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));
}
//deconstructor: cleans up allocated memory
Food::~Food() 
{
    //checking if pointer exists before deleting
    if (foodPos.pos) {
        delete foodPos.pos;
        foodPos.pos = nullptr;
    }
}

//generate new random position for food
void Food::generateFood(objPosArrayList* blockOff)
{
    //get board dimensions
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

   
    int minX = 2;
    int maxX = boardSizeX - 3;
    int minY = 2;
    int maxY = boardSizeY - 3;
    
    bool collision;
    
    do {
        // Generate random position within borders
        foodPos.pos->x = minX + (rand() % (maxX - minX + 1));
        foodPos.pos->y = minY + (rand() % (maxY - minY + 1));

        collision = false;
        
        for (int i = 0; i < blockOff->getSize(); i++) {
            if (foodPos.pos->x == blockOff->getElement(i).pos->x && 
                foodPos.pos->y == blockOff->getElement(i).pos->y) {
                collision = true;
                break; 
            }
        }
    } while (collision); 

}


//return current food position
objPos Food::getFoodPos() const
{
    //create new objPos to return
    objPos returnPos;
    returnPos.pos = new Pos;

    //copy current food position and the symbols
    returnPos.pos->x = foodPos.pos->x;
    returnPos.pos->y = foodPos.pos->y;
    returnPos.symbol = foodPos.symbol;
    return returnPos;
}