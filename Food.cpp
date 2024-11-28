#include "Food.h"
#include "MacUILib.h"

Food::Food(GameMechs* thisGMRef) //constructor: initlaizes food object with game mechanics
{
    mainGameMechsRef = thisGMRef; //stores reference to game mechs
    foodPos.pos = new Pos;//allocate memory for food position
    foodPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;;  //start with a fixed position
    foodPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;;  //different from player start
    foodPos.symbol = 'o';
    
    //random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));
}

Food::~Food() //deconstructor: cleans up allocated memory
{
    //checking if pointer exists before deleting
    if (foodPos.pos) {
        delete foodPos.pos;
        foodPos.pos = nullptr;
    }
}

//generate new random position for food
void Food::generateFood(objPos blockOff)
{
    //get board dimensions
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();
    
    
    /*
    //variables for new position 
    int newXvar, newYvar;
    
    do {
        //generate new position between 1 and boardsize-1
        //make sure food isnt on the boarder
        newXvar = (rand() % (boardSizeX - 2)) + 1;
        newYvar = (rand() % (boardSizeY - 2)) + 1;
        
        //calculate distance from player
        //must be more than 2 spaces away i either x or y direction
        int distX = abs(newXvar - blockOff.pos->x);
        int distY = abs(newYvar - blockOff.pos->y);
        
        //if position is far enough from player, use it
        if (distX > 2 || distY > 2) {
            //setting new food position
            foodPos.pos->x = newXvar;
            foodPos.pos->y = newYvar;
            break; 
        }
    } while (true); //try until valid position is found
    */
    int minX = 2;
    int maxX = boardSizeX - 3;
    int minY = 2;
    int maxY = boardSizeY - 3;
    
    do {
        // Generate position well within borders
        foodPos.pos->x = minX + (rand() % (maxX - minX + 1));
        foodPos.pos->y = minY + (rand() % (maxY - minY + 1));
        
    } while (foodPos.pos->x == blockOff.pos->x && 
             foodPos.pos->y == blockOff.pos->y);
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