#include "Game.h"

void
Game::printScoreboard(Player* player)
{
    int maxScoreLen = 0;
    int maxFarkleLen = 0;

    for (auto _player : playerList) {
        if (_player->getScore() >= targetScore) {
            gameoverFlag = true;
            winnerID = _player->getID();
        }
        maxScoreLen = std::max<int>(
          maxScoreLen, std::to_string(_player->getScore()).length());
        maxFarkleLen = std::max<int>(
          maxFarkleLen, std::to_string(_player->getFarkleCount()).length());
    }

    size_t i = 0;
    printTableHelper_1("┌", "┬", "┐", maxNameLen, maxScoreLen, maxFarkleLen);
    for (; i < playerList.size() - 1; i++) {
        printTableHelper_2(playerList[i]->getName(),
                           std::to_string(playerList[i]->getScore()),
                           std::to_string(playerList[i]->getFarkleCount()),
                           maxNameLen,
                           maxScoreLen,
                           maxFarkleLen);
        printTableHelper_1(
          "├", "┼", "┤", maxNameLen, maxScoreLen, maxFarkleLen);
    }
    printTableHelper_2(playerList[i]->getName(),
                       std::to_string(playerList[i]->getScore()),
                       std::to_string(playerList[i]->getFarkleCount()),
                       maxNameLen,
                       maxScoreLen,
                       maxFarkleLen);
    printTableHelper_1("└", "┴", "┘", maxNameLen, maxScoreLen, maxFarkleLen);

    std::cout << std::endl
              << "Current player is " << player->getName() << std::endl;
}

void
Game::printTableHelper_1(std::string a,
                         std::string b,
                         std::string c,
                         int len1,
                         int len2,
                         int len3)
{
    std::cout << a;
    for (size_t i = 0; i < len1; i++) {
        std::cout << "─";
    }

    std::cout << b;
    for (size_t i = 0; i < len2; i++) {
        std::cout << "─";
    }

    std::cout << b;
    for (size_t i = 0; i < len3; i++) {
        std::cout << "─";
    }

    std::cout << c << std::endl;
}

void
Game::printTableHelper_2(std::string str1,
                         std::string str2,
                         std::string str3,
                         int len1,
                         int len2,
                         int len3)
{
    std::cout << "│" << str1;
    for (size_t i = 0; i < len1 - str1.length(); i++) {
        std::cout << " ";
    }

    std::cout << "│" << str2;
    for (size_t i = 0; i < len2 - str2.length(); i++) {
        std::cout << " ";
    }

    std::cout << "│" << str3;
    for (size_t i = 0; i < len3 - str3.length(); i++) {
        std::cout << " ";
    }

    std::cout << "│" << std::endl;
}

Game::Game()
  : round(0)
  , playerNum(0)
  , maxNameLen(0)
  , targetScore(0)
  , minimumScore(0)
  , gameoverFlag(false)
  , winnerID(NULL)
{
    initGame();
}

int
Game::initGame()
{
    char targetIn, minIn;

    std::cout << "Set the TARGET SCORE:\n[1] 5,000 points\n[2] 10,000 "
                 "points\n[3] 15,000 points"
              << std::endl;

    std::cin >> targetIn;

    switch (targetIn) {
        case '1':
            targetScore = 5000;
            break;
        case '2':
            targetScore = 10000;
            break;
        case '3':
            targetScore = 15000;
            break;
        default:
            break;
    }

    std::cout
      << "Set the MINIMUM SCORE required to roll before saving points\n[1] 350 "
         "points\n[2] 500 points\n[3] 750 points\n[4] 1000 points"
      << std::endl;

    std::cin >> minIn;

    switch (minIn) {
        case '1':
            minimumScore = 350;
            break;
        case '2':
            minimumScore = 500;
            break;
        case '3':
            minimumScore = 750;
            break;
        case '4':
            minimumScore = 1000;
            break;
        default:
            break;
    }

    std::cout << "Please input the number of players:" << std::endl;
    std::cin >> playerNum;

    std::string _order;

    for (size_t i = 0; i < playerNum; i++) {
        std::string _username;

        switch (i) {
            case 0:
                _order = std::string("1st");
                break;

            case 1:
                _order = std::string("2nd");
                break;

            default:
                _order = std::string(std::to_string(i + 1) + "th");
                break;
        }

        std::cout << "Please input the username of the " << _order
                  << " player:" << std::endl;
        std::cin >> _username;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        maxNameLen = std::max<int>(maxNameLen, _username.length());
        playerList.push_back(
          new Player(i, _username, scoreTable, targetScore, minimumScore));
    }

    return 0;
}

int
Game::startGame()
{
    for (int i = 0; i <= playerNum; i++) {
        system("cls");
        if (i == playerNum) {
            i = 0;
        }
        printScoreboard(playerList[i]);

        if (gameoverFlag) {
            std::cout << "Game over! "
                      << "Player " << playerList[winnerID]->getName()
                      << " is the WINNER!" << std::endl;
        }

        playerList[i]->newRound();
    }
    return 0;
}

int
Game::restartGame()
{
    return 0;
}
