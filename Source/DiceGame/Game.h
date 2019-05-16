#pragma once
#include "stdafx.h"

#include <map>
#include <vector>

#include "CombiSchema.h"
#include "Player.h"

class Game
{
  private:
    /* Attributions */
    int round;
    int playerNum;
    int maxNameLen;
    int targetScore;
    int minimumScore;
    bool gameoverFlag;
    int winnerID;

    std::vector<Player*> playerList;

    std::map<CombiSchema, int> scoreTable{
        { CombiSchema("100000"), 100 },  { CombiSchema("000010"), 50 },
        { CombiSchema("300000"), 1000 }, { CombiSchema("030000"), 200 },
        { CombiSchema("003000"), 300 },  { CombiSchema("000300"), 400 },
        { CombiSchema("000030"), 500 },  { CombiSchema("000003"), 600 }
    };

    void printScoreboard(Player* player);

    void printTableHelper_1(std::string a,
                            std::string b,
                            std::string c,
                            int len1,
                            int len2,
                            int len3);

    void printTableHelper_2(std::string str1,
                            std::string str2,
                            std::string str3,
                            int len1,
                            int len2,
                            int len3);

  public:
    /* Functions */
    Game();

    Game(int round, int playerNum);

    ~Game() {}

    int initGame();

    int startGame();

    int restartGame();
};
