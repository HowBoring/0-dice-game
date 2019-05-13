#pragma once
#include "stdafx.h"

#include "CombiSchema.h"
#include "Player.h"
#include <map>
#include <vector>

class Game
{
  private:
    /* Attributions */
    int round;
    int playerNum;

    const std::map<CombiSchema, int> scoreTable{
        { CombiSchema("100000"), 100  },
		{ CombiSchema("000010"), 50   },
        { CombiSchema("300000"), 1000 },
		{ CombiSchema("030000"), 200  },
        { CombiSchema("003000"), 300  },
		{ CombiSchema("000300"), 400  },
        { CombiSchema("000030"), 500  },
		{ CombiSchema("000003"), 600  }
    };

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
