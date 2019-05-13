#pragma once
#include "stdafx.h"

#include "CombiSchema.h"
#include "Dice.h"
#include <map>
#include <vector>

class Player
{
  private:
    int userID;
    std::string username;
    std::vector<Dice> currDiceList;
    std::vector<Dice> asideDiceList;
    std::vector<int> scoreList;
    int currScore;
    int totalScore;
    std::map<CombiSchema, int>& scoreTable;

    // If all the dices are put aside, take a BONUS ROLL.
    int getBonusRoll();

    // Judging whether it's a FARKLE.
    bool isFarkle();

  public:
    Player(int userID,
           std::string& username,
           std::map<CombiSchema, int>& scoreTable);
    ~Player();

    // Return the name of the player.
    const std::string& getName();

    // Start a new roll of dice.
    int playNewRound();

    // Roll the dices in `currDiceList`.
    int rollDices();

    // Calculate the score of dices combination in `currDiceList`.
    int calculateScore();

    // Evaluate the score of dices combination given.
    int evaluateScore(std::vector<int>& selectList);
};
