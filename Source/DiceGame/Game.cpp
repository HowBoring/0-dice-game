#include "Game.h"

Game::Game()
  : round(0)
  , playerNum(0)
{
    initGame();
}

Game::Game(int round, int playerNum)
  : round(round)
  , playerNum(playerNum)
{
    initGame();
}

int
Game::initGame()
{
    return 0;
}

int
Game::startGame()
{
    return 0;
}

int
Game::restartGame()
{
    return 0;
}
