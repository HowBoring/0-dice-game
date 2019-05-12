#pragma once
#include "stdafx.h"

#include "Dice.h"
#include <vector>

class Player
{
  private:
    /* Attributions */
    int userID;
    std::string username;
    std::vector<Dice> currDiceList;
    std::vector<Dice> asideDiceList;
    std::vector<Dice> scoreList;
    int currScore;
    int totalScore;

    int getBonusRoll();

  public:
    /* Functions */
    Player(int userID, std::string& username);
    ~Player();

    const std::string& getName();

    int playNewRound();

    int rollDices();

    bool isFarkle();
};
