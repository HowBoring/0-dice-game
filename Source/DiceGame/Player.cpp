#include "Player.h"

int
Player::getBonusRoll()
{
    return 0;
}

Player::Player(int userID,
               std::string& username,
               std::map<CombiSchema, int>& scoreTable)
  : userID(userID)
  , username(username)
  , scoreTable(scoreTable)
  , currScore(0)
  , totalScore(0)
{}

Player::~Player() {}

const std::string&
Player::getName()
{
    return username;
}

int
Player::playNewRound()
{
    return 0;
}

int
Player::rollDices()
{
    return 0;
}

bool
Player::isFarkle()
{
    return false;
}

int
Player::calculateScore()
{
    return 0;
}

int
Player::evaluateScore(std::vector<int>& selectList)
{
    return 0;
}
