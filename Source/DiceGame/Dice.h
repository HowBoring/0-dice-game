#pragma once
#include "stdafx.h"

#include <array>
#include <random>

class Dice
{
  private:
    // The point of dice, must be in range 1 to 6, but default to 0.
    int dicePoint;

    // Random number generator.
    std::random_device r;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> uniform_dist;


  public:
    Dice();
    Dice(const Dice& dice);
    ~Dice();

    // Converting point to pips.
    std::array<std::string, 5> getPips(int point);

	// Print the pips of current point.
    int printPips();

    // Print the pips of given point.
    int printPips(int point);

    // A public function to change the `dicePoint`.
    int setDicePoint(int point);

    // Return the `dicePoint`.
    int getPoint() const;

    // Make a roll of dice, return the point.
    int roll();

    Dice& operator=(const Dice& _dice);
};