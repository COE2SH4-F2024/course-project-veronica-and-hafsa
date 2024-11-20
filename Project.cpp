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
    if (MacUILib_hasChar()) { // Check if there's input
        char input = MacUILib_getChar(); // Capture the input
        std::cout << "Captured input: " << input << std::endl; // Debug the input

        if (input == 27) { // ESC key (ASCII value 27)
            std::cout << "Exit key pressed. Exiting game." << std::endl;
            exitFlag = true;
        } else {
            gameMechs->setInput(input); // Pass the input to GameMechs
            player->updatePlayerDir();  // Update the player's direction
        }
    }
}

void RunLogic(void)
{
    player->movePlayer(); // move player based on the updated direction
}

void DrawScreen(void)
{
   // Step 1: Clear the screen
    MacUILib_clearScreen();

    // Step 2: Get the player's current position
    int x = player->getPlayerPos().pos->x;
    int y = player->getPlayerPos().pos->y;

    // Debug: Print current position
    std::cout << "Drawing player at position: (" << x << ", " << y << ")" << std::endl;

    // Step 3: Move the cursor vertically (to the correct Y position)
    for (int i = 0; i < y; ++i) {
        std::cout << std::endl; // Add a newline for each row
    }

    // Step 4: Move the cursor horizontally (to the correct X position)
    for (int i = 0; i < x; ++i) {
        std::cout << " "; // Add spaces to move horizontally
    }

    // Step 5: Draw the player's symbol (*)
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
