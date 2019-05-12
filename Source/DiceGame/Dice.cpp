#include "Dice.h"

Dice::Dice() {}

Dice::~Dice() {}

int
Dice::printPips(int point)
{
    std::string pips;

    switch (point) {
        case 1:
            pips = "┌───────┐"
                   "│       │"
                   "│   ●   │"
                   "│       │"
                   "└───────┘";
        case 2:
            pips = "┌───────┐"
                   "│       │"
                   "│ ●   ● │"
                   "│       │"
                   "└───────┘";
        case 3:
            pips = "┌───────┐"
                   "│ ●     │"
                   "│   ●   │"
                   "│     ● │"
                   "└───────┘";
        case 4:
            pips = "┌───────┐"
                   "│ ●   ● │"
                   "│       │"
                   "│ ●   ● │"
                   "└───────┘";
        case 5:
            pips = "┌───────┐"
                   "│ ●   ● │"
                   "│   ●   │"
                   "│ ●   ● │"
                   "└───────┘";

        case 6:
            pips = "┌───────┐"
                   "│ ●   ● │"
                   "│ ●   ● │"
                   "│ ●   ● │"
                   "└───────┘";

        default:
            break;
    }

    std::cout << pips;
    return 0;
}