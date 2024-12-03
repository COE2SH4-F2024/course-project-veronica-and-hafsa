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

    //create game object
    gameMechs = new GameMechs(30,15); // board game dimensions
    food = new Food(gameMechs); //create food with object reference
    player = new Player(gameMechs,food); //create player object with game mech and food
    


    //initial food position
    objPos playerPos = player->getPlayerPos()->getHeadElement();
}


void GetInput(void)
{
    //check if there is any user input
    if (MacUILib_hasChar()) {
        char newInput = MacUILib_getChar(); //read the input character
        gameMechs->setInput(newInput); //store input for processing
    }
}


void RunLogic(void){
    char input = gameMechs->getInput(); //retrieve the stored input
   
    //if player presses exit key or collides with itself, shutdown the game: 
    if (input == 27 || player->checkSelfCollision()) { 
        gameMechs->setExitTrue();
    }

    else {
        //update player position
        player->updatePlayerDir();
        player->movePlayer();
    }
   
    gameMechs->clearInput(); //clear processed input

}



    


void DrawScreen(void){


    MacUILib_clearScreen();

    //retrieve players head position
    objPos playerHead = player->getPlayerPos()->getHeadElement();
    objPosArrayList* playerPos = player->getPlayerPos();
    int playerSize = playerPos-> getSize();

    //retrieve current food position
    objPos foodPos = food->getFoodPos();


    //display game information
    MacUILib_printf("Score= %d\n", gameMechs->getScore());
   
    //display game status
    if (gameMechs->getExitFlagStatus()){
        MacUILib_printf("You lost the game!\n");
        MacUILib_Delay(DELAY_CONST); // 0.1s delay before game shuts down

    } else {
        MacUILib_printf("You survived the game!\n");
    }
   
    //draw the board
    for (int y = 0; y < gameMechs->getBoardSizeY(); y++)
    {
        for (int x = 0; x < gameMechs->getBoardSizeX(); x++)
        {
            bool playerelement = false;

            //check if current position matches player segement
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

            // If not a player segment, check for other obejcts
            if (!playerelement)
            {
                if (y == 0 || y == gameMechs->getBoardSizeY() - 1 ||
                    x == 0 || x == gameMechs->getBoardSizeX() - 1)
                {
                    MacUILib_printf("#");  //print game boarders
                }
                else if (x == foodPos.pos->x && y == foodPos.pos->y)
                {
                    MacUILib_printf("o"); //print food
                }
                else
                {
                    MacUILib_printf(" "); //print empty spaces
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
