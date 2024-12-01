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
    food = new Food(gameMechs); //create food
    player = new Player(gameMechs,food); // pass gameMechs referece to the player
    


    //initial food position
    objPos playerPos = player->getPlayerPos()->getHeadElement();


    //generate food
    //food->generateFood(playerPos);
   
    //get and print new food position
    //objPos foodPos = food->getFoodPos();
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
    if (input == 27 || player->checkSelfCollision()) { // ESC key
        //MacUILib_printf("You lose the game!");
        gameMechs->setExitTrue();
    }

    else {
        //update player position
        player->updatePlayerDir();
        player->movePlayer();


        //checking for food collision
        /*objPos playerPos = player->getPlayerPos();
        objPos foodPos = food->getFoodPos();
       
        if(playerPos.pos->x == foodPos.pos->x &&
           playerPos.pos->y == foodPos.pos->y)
        {
            food->generateFood(playerPos); //generate new food
            gameMechs->incrementScore();  // optional---> increase score when food is eaten
        }*/
    }
   
    gameMechs->clearInput(); //clear processed input

}



    


void DrawScreen(void){


    MacUILib_clearScreen();

    objPos playerHead = player->getPlayerPos()->getHeadElement();
    objPosArrayList* playerPos = player->getPlayerPos();
    int playerSize = playerPos-> getSize();

    objPos foodPos = food->getFoodPos();


    //display game information
    MacUILib_printf("Score= %d\n", gameMechs->getScore());
   
    //display game status
    if (gameMechs->getExitFlagStatus()){
        MacUILib_printf("You lost the game!\n");
        MacUILib_Delay(999999); // 0.1s delay

    } else {
        MacUILib_printf("You survived the game!\n");
    }
   
    //draw the board

    for (int y = 0; y < gameMechs->getBoardSizeY(); y++)
    {
        for (int x = 0; x < gameMechs->getBoardSizeX(); x++)
        {
            bool playerelement = false;

            for (int k = 0; k < playerPos->getSize(); k++)
            {
                objPos thisSeg = playerPos->getElement(k);
                if (thisSeg.pos->x == x && thisSeg.pos->y == y)
                {
                    playerelement = true;
                    MacUILib_printf("%c", thisSeg.symbol); // Print the player's segment
                    break; 
                }
            }

            // If not a player segment, check for walls, food, or empty space
            if (!playerelement)
            {
                if (y == 0 || y == gameMechs->getBoardSizeY() - 1 ||
                    x == 0 || x == gameMechs->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#"); 
                }
                else if (x == foodPos.pos->x && y == foodPos.pos->y)
                {
                    MacUILib_printf("o"); 
                }
                else
                {
                    MacUILib_printf(" "); 
                }
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
    delete food; //free food memory
    MacUILib_uninit();
}
