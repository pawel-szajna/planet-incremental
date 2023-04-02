#include "game/Game.hpp"

#include <iostream>
#include <stdexcept>

int main()
try
{
    Game::Game game;
    game.start();
    return 0;
}
catch (std::exception e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
