#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
GameMechs* gameMechs = nullptr;
Player* player = nullptr;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    gameMechs = new GameMechs(30,15); // board game
    player = new Player(gameMechs); // pass gameMechs referece to the player

}

void GetInput(void)
{
    if (MacUILib_hasChar()) { 
        char input = MacUILib_getChar(); 
        std::cout << "Captured input: " << input << std::endl; //DEBUGGG
        if (input == 27) { // ESC key (ASCII value 27)
            exitFlag = true;
            return;
        }

        gameMechs->setInput(input); //pass the input to GameMechs
        player->updatePlayerDir();  //update the player's direction
        }
}


void RunLogic(void)
{
    player->movePlayer(); //move player based on the updated direction
}

void DrawScreen(void)
{
   //clear the screen
    MacUILib_clearScreen();

    //get the player's current position
    int x = player->getPlayerPos().pos->x;
    int y = player->getPlayerPos().pos->y;

    //DEBUGGG: print current position
    std::cout << "Drawing player at position: (" << x << ", " << y << ")" << std::endl;

    //move the cursor vertically (to the correct Y position)
    for (int i = 0; i < y; ++i) {
        std::cout << std::endl; 
    }

    //move the cursor horizontally (to the correct X position)
    for (int i = 0; i < x; ++i) {
        std::cout << " "; 
    }

    //draw the player's symbol (*)
    std::cout << "*" << std::endl;
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

    MacUILib_uninit();
}
