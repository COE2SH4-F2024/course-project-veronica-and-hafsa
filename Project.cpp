#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"


using namespace std;

#define DELAY_CONST 100000 //gmaeloop delay constat

//global pounters for the game ojects
GameMechs* gameMechs = nullptr;  //game mech objecy
Player* player = nullptr;       //player pbject
Food* food = nullptr;          //food object


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();
    while (!gameMechs->getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
    return 0;

    
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameMechs = new GameMechs(30,15); // board game
    player = new Player(gameMechs); // pass gameMechs referece to the player
    food = new Food(gameMechs); //create food

    //initial food position
    objPos playerPos = player->getPlayerPos();

    //generate food
    food->generateFood(playerPos);
    
    //get and print new food position
    objPos foodPos = food->getFoodPos();
}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        char newInput = MacUILib_getChar();
        gameMechs->setInput(newInput); //store input for processing
    }
}


void RunLogic(void){
    char input = gameMechs->getInput();
    
    //check for exit command
    if (input == 27) { // ESC key
        gameMechs->setExitTrue();
    }
    //check for lose command
    else if(input=='.'){
        gameMechs->setLoseFlag();
    } 
    else {
        //update player position
        player->updatePlayerDir();
        player->movePlayer();

        //checking for food collision
        objPos playerPos = player->getPlayerPos();
        objPos foodPos = food->getFoodPos();
        
        if(playerPos.pos->x == foodPos.pos->x && 
           playerPos.pos->y == foodPos.pos->y)
        {
            food->generateFood(playerPos); //generate new food
            gameMechs->incrementScore();  // optional---> increase score when food is eaten
        }
    }
    
    gameMechs->clearInput(); //clear processed input
}

void DrawScreen(void){

    MacUILib_clearScreen();

    //current positions
    objPos playerHead = player->getPlayerPos();
    objPos foodPos = food->getFoodPos();

    //display debug information
    MacUILib_printf("Debug - Player at: x=%d, y=%d\n", playerHead.pos->x, playerHead.pos->y);
    MacUILib_printf("Debug - Score= %d\n", gameMechs->getScore());
    MacUILib_printf("Debug- Press spacebar to increment score:\n");
    MacUILib_printf("Debug - Food at: x=%d, y=%d\n", foodPos.pos->x, foodPos.pos->y);
    
    //display game status
    if (gameMechs->getLoseFlagStatus()){
        MacUILib_printf("You lost the game!\n");
        cout << "Lose Flag Status:" << boolalpha << gameMechs->getLoseFlagStatus() << endl;
    } else {
        MacUILib_printf("You survived the game!\n");
        cout << "Lose Flag Status:" << boolalpha << gameMechs->getLoseFlagStatus() << endl;
    }
    
    //draw the board
    for(int y = 0; y < gameMechs->getBoardSizeY(); y++)
    {
        for(int x = 0; x < gameMechs->getBoardSizeX(); x++)
        {
            if(y == 0 || y == gameMechs->getBoardSizeY()-1 || 
               x == 0 || x == gameMechs->getBoardSizeX()-1)
            {
                MacUILib_printf("#"); //draw the board
            }
            else if(x == playerHead.pos->x && y == playerHead.pos->y)
            {
                MacUILib_printf("*"); //draw the player
            }
            else if(x == foodPos.pos->x && y == foodPos.pos->y)
            {
                MacUILib_printf("o"); //draw food
            }
            else
            {
                MacUILib_printf(" "); //empty spaces
            }
        }
        MacUILib_printf("\n");
    }
    
    //clean up temporary objPos
    delete foodPos.pos;

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  

    delete player; //free memory for player
    delete gameMechs;//free memory for gamemechs  
    delete food; //free food memory
    MacUILib_uninit();
}