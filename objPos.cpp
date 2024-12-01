#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

//default constructor
objPos::objPos()
{

    pos = new Pos; //allocate memory for position
    pos->x = 0;    //initalize x-coord 
    pos->y = 0;    //initalize y-coord
    symbol = 0; //NULL
}


objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}


//deconstructor
objPos::~objPos()
{
    delete pos; // Clean up memory
}

//set the position and symbol using individual parameters
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//set the position and symbol using individual parameters
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//get a copy of the objPos object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}
//get symbol of the objPos
char objPos::getSymbol() const
{
    return symbol;
}

//check if this position is equal to another position
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y); //compare x and y coordinates
}

//get the symbol if this position is equal to another positon
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos)) //check if positions are equal
        return symbol;     //return the symbol if =
    else
        return 0; //NULL
}

//copy constructor
objPos::objPos(const objPos& other)
{
    pos = new Pos;             //allocate new memory for position
    pos->x = other.pos->x;     //copy x coord
    pos->y = other.pos->y;     //copy y coord
    symbol = other.symbol;     //copy symbol
}

//assignment operator
objPos& objPos::operator=(const objPos& other)
{
    if (this == &other) 
        return *this;

    delete pos; //delete existing memory

    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;  //return current object
}

