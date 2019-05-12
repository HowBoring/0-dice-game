#pragma once
#include "stdafx.h"

#include "Player.h"
#include <vector>

class Game
{
  private:
    /* Attributions */
    int round;
    int playerNum;
    std::vector<Player> playerList;

  public:
    /* Functions */
    Game();

    Game(int round, int playerNum);

    ~Game() {}

    int initGame();

    int startGame();

	int restartGame();
};
