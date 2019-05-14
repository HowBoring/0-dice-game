#include "Player.h"

Player::Player(int userID,
               std::string& username,
               std::map<CombiSchema, int>& scoreTable)
  : userID(userID)
  , username(username)
  , scoreTable(scoreTable)
  , currScore(0)
  , totalScore(0)
{
    scoreList.clear();
}

Player::~Player() {}

const std::string&
Player::getName()
{
    return username;
}

int
Player::playNewRound()
{
    initRound();

    while (true) {
        rollDices();
        printRollRst();

        // If FARKLE, set the score 0, return.
        if (isFarkle()) {
            currScore = 0;
            scoreList.back() = 0;
            printTips("You get a FARKLE!!");
            return 1;
        }

        bool flag = true;
        int keyNum;
        std::vector<int> selectList;

        printTips(
          "Choose your dice combination: (serial numbers, end with return)");

        while (true) {
            do {
                std::cin >> keyNum;
                if (!std::cin) {
                    flag = false;
                    break;
                }
                selectList.push_back(keyNum);
            } while (std::cin.get() != '\n');

            if (flag) {
                selectList.clear();
                printTips("Input type error, please try again.");
                continue;
            }

            if (selectList.size() > currDiceList.size()) {
                selectList.clear();
                printTips("Input too much, please try again.");
                continue;
            }

            currScore = evaluateCombination(selectList);

            if (currScore == 0) {
                selectList.clear();
                printTips("Invalid combination, please try again.");
                continue;
            }

            break;
        }

        selectCombination(selectList);
        scoreList.back() += currScore;

        if (isBonus()) {
            printTips("You get a BONUS ROLL!!");
            initRound();
            continue;
        }

        std::string inputStr;
        printTips("End this round and save the score? (Y/n)");

        while (true) {
            std::cin >> inputStr;
            if (inputStr == "Y" || inputStr == "y" || inputStr == "N" ||
                inputStr == "n") {
                break;
            }

            printTips("Wrong input. Try again.");
        }

        if (inputStr == "Y" || inputStr == "y") {
            break;
        }
    }

    return 0;
}

void
Player::initRound()
{
    currDiceList.clear();
    asideDiceList.clear();
    currScore = 0;

    for (size_t i = 0; i < 6; i++) {
        currDiceList.push_back(Dice());
    }

    // Create a score for the NEW round.
    scoreList.push_back(0);
}

void
Player::rollDices()
{
    for (auto dice : currDiceList) {
        dice.roll();
    }
}

void
Player::selectCombination(const std::vector<int>& selectList)
{
    for (auto diceOrder : selectList) {
        asideDiceList.push_back(currDiceList[diceOrder - 1]);
        currDiceList.erase(currDiceList.begin() + diceOrder - 1);
    }
}

int
Player::evaluateCombination(const std::vector<int>& selectList)
{
    CombiSchema _selectSchema = getSchema(selectList);
    if (scoreTable.find(_selectSchema) == scoreTable.end()) {
        return 0;
    } else {
        return scoreTable[_selectSchema];
    }
}

bool
Player::isFarkle()
{
    CombiSchema _currSchema = getCurrSchema();

    // If the current situation DOES include any scoring method,
    // then return false.
    for (auto schema : scoreTable) {
        if (CombiSchema(_currSchema).contain(schema.first)) {
            return false;
        }
    }

    return true;
}

bool
Player::isBonus()
{
    // An empty `currDiceList` means a BONUS ROLL.
    return currDiceList.empty();
}

CombiSchema
Player::getCurrSchema()
{
    std::vector<int> _currList;
    for (size_t i = 0; i < currDiceList.size(); i++) {
        _currList.push_back(i);
    }
    return getSchema(_currList);
}

CombiSchema
Player::getSchema(const std::vector<int>& selectList)
{
    int _currSchema[]{ 0, 0, 0, 0, 0, 0 };

    // Statistics the current number of dice points.
    for (int diceOrder : selectList) {
        _currSchema[currDiceList[diceOrder].getPoint()]++;
    }

    return CombiSchema(_currSchema);
}

int
Player::getBonusRoll()
{
    return 0;
}

void
Player::printRollRst()
{
    char i = 'a';
    for (auto dice : currDiceList) {
        std::cout << i++ << ". [" << dice.getPoint() << "] ";
    }
}

void
Player::printTips(std::string tips)
{
    std::cout << tips << std::endl;
}

int
Player::calculateScore()
{
    return 0;
}