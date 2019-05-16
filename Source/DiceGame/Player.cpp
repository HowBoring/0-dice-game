#include "Player.h"

Player::Player(int userID,
               std::string username,
               std::map<CombiSchema, int>& scoreTable,
               int targetScore,
               int minimumScore)
  : userID(userID)
  , username(username)
  , scoreTable(scoreTable)
  , targetScore(targetScore)
  , minimumScore(minimumScore)
  , bonusFlag(false)
  , stopFlag(false)
  , farkleFlag(false)
  , selectFlag(false)
  , invalidFlag(false)
  , currScore(0)
  , localScore(0)
  , consecutiveFarkle(0)
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
Player::getID()
{
    return userID;
}

int
Player::getScore()
{
    return currScore;
}

int
Player::getFarkleCount()
{
    return consecutiveFarkle;
}

void
Player::initRound()
{
    bonusFlag = stopFlag = farkleFlag = selectFlag = invalidFlag = false;
    currDiceList.clear();
    asideDiceList.clear();

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
Player::selectCombi(const std::vector<int>& selectList)
{
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
    std::cout << std::endl;
    char i = '1';
    for (auto dice : currDiceList) {
        std::cout << i++ << ". [" << dice->getPoint() << "]   ";
    }
    std::cout << std::endl;
}

void
Player::printRollRst(int)
{
    std::cout << std::endl;
    for (size_t i = 0; i < 5; i++) {
        for (auto dice : currDiceList) {
            std::cout << dice->getPips(dice->getPoint())[i] << "   ";
        }
        std::cout << std::endl;
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
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    currScore += scoreList.back();
    return currScore;
}

int
Player::newRound()
{
    initRound();

    do {
        stopFlag = false;
        selectList.clear();
    } while (rollLoop() && !farkleFlag);

    calculateScore();

    printTips("You finally get " + std::to_string(scoreList.back()) +
              " scores in this round.");
    printTips("Your turn is over.");

    printTips("The cumulative score is " + std::to_string(currScore) +
              " scores.");

    if (!farkleFlag) {
        consecutiveFarkle = 0;
    } else if (consecutiveFarkle == 3) {
        currScore = std::max<int>(0, currScore - 1000);
        consecutiveFarkle = 0;
    }

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

    if (farkleFlag) {
        return 0;
    }

    if (scoreList.back() < minimumScore) {
        printTips("Your score is not up to the minimum requirement for the "
                  "time being and cannot be saved.");
        std::cin.get();
        return 1;
    }

    stopFlag = optionInteractive("Stop and save score? (y/n)");

    if (stopFlag) {
        return 0;
    }

    return 1;
}

int
Player::bonusLoop()
{
    printTips("\n================================ DICES ROLLING "
              "=================================");
    rollDices();

    // Cheating for testing~
    // for (auto i : currDiceList) {
    //     i->setDicePoint(1);
    // }

    if (isFarkle()) {
        printTips("\n******************************** YOU GET FARKLE "
                  "********************************");
        printRollRst(0);
        farkleFlag = true;
        consecutiveFarkle++;
        eraseScore();
        return 0;
    }

    do {
        selectFlag = false;
        // currScore = 0;
    } while (selectLoop());

    if (isBonus()) {
        printTips("\n################################ BONUS ROLLING "
                  "#################################");
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
    scoreList.back() += localScore;

    printTips("You get " + std::to_string(currScore) +
              " scores in this round.");

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
    printRollRst(0);

    printTips(
      "Please select dice combination: (split by SPACE while end by ENTER)");

    std::string inputLine;
    std::getline(std::cin, inputLine);
    // char inputArray[20] = { NULL };
    // std::cin.getline(inputArray, 20);
    // std::string inputLine = std::string(inputArray);
    selectList = split(inputLine, ' ');
    std::sort(selectList.begin(), selectList.end(), [](int x, int y) -> bool {
        return x > y;
    });

    for (auto i : selectList) {
        if (i < 1 || i > currDiceList.size()) {
            printTips("Wrong input, try again.");
            invalidFlag = true;
            return 1;
        }
    }

    localScore = evaluateCombi(selectList);

    if (!localScore) {
        printTips("Wrong combination, try again.");
        invalidFlag = true;
        return 1;
    }

    printTips("You get " + std::to_string(localScore) +
              " scores in this selection.");

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