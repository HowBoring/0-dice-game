// DiceGame.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include "stdafx.h"

#include <map>

#include "CombiSchema.h"
#include "Player.h"

int
main()
{
    std::map<CombiSchema, int> scoreTable{
        { CombiSchema("100000"), 100 },  { CombiSchema("000010"), 50 },
        { CombiSchema("300000"), 1000 }, { CombiSchema("030000"), 200 },
        { CombiSchema("003000"), 300 },  { CombiSchema("000300"), 400 },
        { CombiSchema("000030"), 500 },  { CombiSchema("000003"), 600 }
    };

	int userID = 0;

	std::string username = "Player1";

    Player* p = new Player(userID, username, scoreTable);

	p->playNewRound();

    return 0;
}