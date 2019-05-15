#include "Player.h"

Player::Player(int userID,
               std::string username,
               std::map<CombiSchema, int>& scoreTable)
  : userID(userID)
  , username(username)
  , scoreTable(scoreTable)
  , bonusFlag(false)
  , stopFlag(false)
  , farkleFlag(false)
  , selectFlag(false)
  , invalidFlag(false)
  , currScore(0)
  , localScore(0)
{
    scoreList.clear();
}

Player::~Player() {}

const std::string&
Player::getName()
{
    return username;
}

/*
int
Player::playNewRound()
{
    initRound();

    while (true) {
        rollDices();
        printRollRst();

        // When FARKLE, set score to 0, return.
        if (isFarkle()) {
            currScore = 0;
            scoreList.back() = 0;
            printTips("Unfortunately, you get a FARKLE!!");
            return 1;
        }

        std::string inputLine;
        std::vector<int> selectList;

        // Combination choosing loop.
        while (true) {
            selectList.clear();

            printTips("Choose your dice combination: (serial numbers, split "
                      "with space while end with ENTER)");

            while (true) {
                bool inputValid;
                bool quitFlag = false;

                // Get the user input.
                do {
                    selectList.clear();
                    inputValid = true;

                    std::getline(std::cin, inputLine);

                    // Do nothing in this loop.
                    if (inputLine == "quit") {
                        quitFlag = true;
                        break;
                    }

                    selectList = split(inputLine, ' ');

                    for (auto i : selectList) {
                        if (i < 1 || i > 6) {
                            printTips("Wrong input, try again.");
                            inputValid = false;
                            break;
                        }
                    }
                } while (!inputValid);

                if (quitFlag) {
                    break;
                }

                if (selectList.size() > currDiceList.size()) {
                    printTips("Input too much, please try again.");
                    continue;
                }

                currScore = evaluateCombi(selectList);

                if (!currScore) {
                    printTips("Invalid combination, please try again.");
                    continue;
                }

                break;
            }

            selectCombi(selectList);
            scoreList.back() += currScore;

            std::cout << "You get " << currScore
                      << " score in through this action." << std::endl;

            if (isBonus()) {
                bonusFlag = true;
                break;
            }

            // If the answer is NO, then break.
            if (optionInteractive(
                  "Continue to select dice combinations? (y/n)")) {
                currScore = 0;
                break;
            }

            printRollRst();
        }

        if (bonusFlag) {
            printTips("Congratulations! You get a BONUS ROLL!!");
            initRound();
            continue;
        }

        // If the answer is YES, then break.
        if (!optionInteractive("End this round and save the score? (y/n)")) {
            break;
        }
    }

    return 0;
}
*/

void
Player::initRound()
{
    bonusFlag = stopFlag = farkleFlag = selectFlag = invalidFlag = false;
    currDiceList.clear();
    asideDiceList.clear();
    currScore = 0;

    for (size_t i = 0; i < 6; i++) {
        currDiceList.push_back(new Dice());
    }

    // Create a score for the NEW round.
    scoreList.push_back(0);
}

void
Player::rollDices()
{
    for (auto dice : currDiceList) {
        dice->roll();
    }
}

void
Player::selectCombi(std::vector<int>& selectList)
{
    std::sort(selectList.begin(),
		selectList.end(),
		[](int x, int y) -> bool { return x > y; }
	);

    for (auto diceOrder : selectList) {
        asideDiceList.push_back(currDiceList[(__int64)diceOrder - 1]);
        currDiceList.erase(currDiceList.begin() + diceOrder - 1);
    }
}

int
Player::evaluateCombi(const std::vector<int>& selectList)
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
    // then return false
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
        _currList.push_back(i + 1);
    }
    return getSchema(_currList);
}

CombiSchema
Player::getSchema(const std::vector<int>& selectList)
{
    int _currSchema[]{ 0, 0, 0, 0, 0, 0 };

    // Statistics the current number of dice points.
    for (auto diceOrder : selectList) {
        _currSchema[currDiceList[(__int64)diceOrder - 1]->getPoint() - 1]++;
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
    char i = '1';
    for (auto dice : currDiceList) {
        std::cout << i++ << ". [" << dice->getPoint() << "]   ";
    }
    std::cout << std::endl;
}

void
Player::printTips(std::string tips)
{
    std::cout << tips << std::endl;
}

bool
Player::optionInteractive(std::string question)
{
    std::string inputStr;
    printTips(question);

    while (true) {
        std::cin >> inputStr;
        if (inputStr == "Y" || inputStr == "y" || inputStr == "N" ||
            inputStr == "n") {
            break;
        }

        printTips("Wrong input. Try again.");
    }

    if (inputStr == "Y" || inputStr == "y") {
        return true;
    }

    return false;
}

int
Player::calculateScore()
{
    return 0;
}

int
Player::newRound()
{
    initRound();

    do {
        stopFlag = false;
        selectList.clear();
    } while (rollLoop() && !farkleFlag);
    return 0;
}

int
Player::rollLoop()
{
    do {
        if (bonusFlag) {
            currDiceList.clear();
            asideDiceList.clear();

            for (size_t i = 0; i < 6; i++) {
                currDiceList.push_back(new Dice());
            }
        }
        bonusFlag = false;
    } while (bonusLoop() && !farkleFlag);

    stopFlag = optionInteractive("Stop and save score? (y/n)");

    if (stopFlag) {
        return 0;
    }

    return 1;
}

int
Player::bonusLoop()
{
    rollDices();

    if (isFarkle()) {
        farkleFlag = true;
        eraseScore();
        return 0;
    }

    do {
        selectFlag = false;
        currScore = 0;
    } while (selectLoop());

    if (isBonus()) {
        bonusFlag = true;
        return 1;
    }

    return 0;
}

int
Player::selectLoop()
{
    do {
        invalidFlag = false;
        localScore = 0;
    } while (validLoop());

    selectCombi(selectList);
    scoreList.back() += currScore;

    if (isFarkle()) {
        return 0;
    }

    selectFlag = optionInteractive("Stop to select? (y/n)");

    if (selectFlag) {
        return 0;
    }

    return 1;
}

int
Player::validLoop()
{
    printRollRst();
    printTips(
      "Please select dice combination: (split by SPACE while end by ENTER)");

    std::string inputLine;
    std::getline(std::cin, inputLine);
    selectList = split(inputLine, ' ');

    for (auto i : selectList) {
        if (i < 1 || i > 6) {
            printTips("Wrong input, try again.");
            invalidFlag = true;
            return 1;
        }
    }

    localScore = evaluateCombi(selectList);

    if (!localScore || !selectList.size()) {
        printTips("Wrong combination, try again.");
        invalidFlag = true;
        return 1;
    }

    return 0;
}

int
Player::eraseScore()
{
    currScore = 0;
    scoreList.back() = 0;
    return 0;
}

template<typename Out>
void
split(const std::string& s, char delim, Out result)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = atoi(item.data());
    }
}

std::vector<int>
split(const std::string& s, char delim)
{
    std::vector<int> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}