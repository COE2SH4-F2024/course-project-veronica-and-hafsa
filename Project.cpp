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

    exitFlag = false;

    gameMechs = new GameMechs(30,15); // board game
    player = new Player(gameMechs); // pass gameMechs referece to the player


}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        char newInput = MacUILib_getChar();
        gameMechs->setInput(newInput);
    }
}


void RunLogic(void){
    char input = gameMechs->getInput();
    
    if (input == 27) { // ESC key
        gameMechs->setExitTrue();
    }
    else {
        player->updatePlayerDir();
        player->movePlayer();
    }
    gameMechs->clearInput();
}

void DrawScreen(void){

    MacUILib_clearScreen();

    objPos playerHead = player->getPlayerPos();
    MacUILib_printf("Debug - Player at: x=%d, y=%d\n", playerHead.pos->x, playerHead.pos->y);
    
    //draw the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); y++)
    {
        for (int x = 0; x < gameMechs->getBoardSizeX(); x++)
        {
            bool isBorder = (y == 0 || y == gameMechs->getBoardSizeY() - 1 ||
                           x == 0 || x == gameMechs->getBoardSizeX() - 1);
            
            if (isBorder)
                MacUILib_printf("#");
            else if (x == playerHead.pos->x && y == playerHead.pos->y)
                MacUILib_printf("*");
            else
                MacUILib_printf(" ");
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
