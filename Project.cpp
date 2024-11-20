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

    gameMechs-> getInput();
}


void RunLogic(void)
{
    if (MacUILib_hasChar()) { 
        char input = MacUILib_getChar(); 
        std::cout << "Captured input: " << input << std::endl; //DEBUGG
        
        if (input == 27) { // ESC key (ASCII value 27)
            exitFlag = true;
            return;
        }

        gameMechs->setInput(input);
        player->updatePlayerDir(); 
        std::cout << "Direction updated to: " << player->getPlayerPos().pos->x << ", " << player->getPlayerPos().pos->y << std::endl;
    }

    if(gameMechs->getInput() == ' '){
        gameMechs->setExitTrue(); 
    }
    else{
        player->updatePlayerDir();
        player->movePlayer();
    }

    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    
    int totalRows = gameMechs->getBoardSizeY();
    int totalCols = gameMechs->getBoardSizeX();

    //get the player's current position
    objPos playerHead = player->getPlayerPos();

    //iterate over the game board to draw each cell
    for (int row = 0; row < totalRows; ++row)
    {
        for (int col = 0; col < totalCols; ++col)
        {

            if (row == 0 || row == totalRows - 1 || col == 0 || col == totalCols - 1)
            {
                MacUILib_printf("#");
            }

            else if (playerHead.pos->x == col && playerHead.pos->y == row)
            {
                MacUILib_printf("%c", playerHead.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); 
    }
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
