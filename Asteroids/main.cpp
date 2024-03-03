#include <SFML/Graphics.hpp>
#include "Game.h"

int main() 

{
    // Set seed for random number generator
    srand((int)time(0));

    // Run the game
    Game game;
    game.Run();

    return 0;
}