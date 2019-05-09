# Assignment Task: Farkle (a dice game)

## Game Overview

In this assignment, you are to write dice game, where you roll six dice to create a range of
scoring combinations. The first player to reach or exceed the target score is declared the
winner! Any number of players may play, however, for the basic assignment you only need to
implement one.

## Basic Game Play

In this program, you will control a set of six dice. On your turn, you must make as many scoring
combinations (as outlined below) as you wish to score points towards the winning target score.
The basic game play is as follows:

- One player is randomly chosen to go first. Players take turns in clockwise order. The game is played in rounds in which each player has a turn to roll the dice and score points.
- On your turn:
  - Roll all six dice and set aside at least one die of a scoring value, (as shown below):
  
    | Dice  | Points   | Dice  | Points |
    | ----- | -------- | ----- | ------ |
    | 1’s   | 100 each | 3x3's | 300    |
    | 5’s   | 50 each  | 3x4's | 400    |
    | 3x1's | 1000     | 3x5's | 500    |
    | 3x2's | 200      | 3x6's | 600    |

    Combinations only count when made in a single throw.
   - You may now decide whether to score your points and end your turn or you can re-roll the remaining dice.
   - If you choose to roll again, you can keep rolling the dice, until you choose to stop or you roll no scoring values. Rolling no scoring values is called a FARKLE.
   - If you roll a FARKLE, you score NO POINTS for this round and your turn ends. Pass the dice to the next player.
   - If you set aside all 6 dice, you may re-roll all 6 dice and continue adding to your score, following all the rules above.
 - The first player to score 5,000 or more points wins the game.

There are many variations to this basic game, some of which you will be able to implement as
part of the extra functionality for your assignment.

## A Typical Player Turn

During a player’s turn, the logic is as follows:

1. First, the player must roll all 6 dice to produce 6 random numbers from 1-6.
2. Next, they set aside at least one die that scores points (a single 1 or 5, or 3-of-a-kind). The points for which are stored in a running total for the player’s turn. These dice cannot be rolled again, until after all 6 dice are set aside (see Step 4).
3. The player is presented with 2 options – roll the dice or score their points.

    If they choose to score, the running total is added to their player score and their turn ends.

    If they roll again, only those dice not set aside are rolled. Steps 2 and 3 may be repeated as often as the player wishes, until they use all 6 dice (Step 4) or roll a Farkle (Step 5).

4. If the player sets aside all 6 dice, they start again with all 6 dice and continue scoring as before this is called a Bonus Roll. Steps 2 and 3 may be repeated as often as the player wishes.
5. A Farkle is a roll with no scoring values – the player cannot take a single 1 or 5, or 3-of-a-kind. When this happens, the player ends their turn immediately and does not score the points rolled during that turn. Their saved score is not changed.

Here is an example roll for a player’s turn:

- On their first roll, the player rolls a 1, 2, 3, 3, 5, 5.
- They can score 100 points for the 1, or 100 points for both 5s, or 50 points for 1 of the 5s, or 200 points for the 1 and both 5s.
- They choose to set aside just the 1 for 100 points and roll the 5 remaining dice again.
- This time they roll a 2, 3, 6, 6, 6. They decide to take the 600 points for the 3-of-a-kind in
6s.
- Their running total is now 700 points. This is a good score so they opt to save their points
and end their turn.

## Extra Functionality

The marking criteria indicates that you should make some individual additions to this in order to
achieve the final 20% of the mark.

Following is a list of additional features you can include, with the maximum number of marks **\[x\]** you can earn for each one. You may implement one or more features from the list, but you will only be able to score a maximum of 20% of the marks (a total of 20 marks).

1. Include multiple human players making the game playable by 1 to 4 people. At the beginning of the game the player order must be randomised. Each player must track their own score and display their name and game score when required. **\[3\]**
2. If a player rolls three Farkles in a row (on three consecutive turns) they lose 1000 points from their saved score. Once they lose the points the counter for Farkles is reset to zero. **\[3\]**
3. Allow the players to choose the target score and the minimum points required to roll before saving points. Targets = 5,000 points, 10,000 points or 15,000 points. Minimum roll required = 350 points, 500 points, 750 points or 1000 points. **\[4\]**
4. Display the dice using ASCII art, showing the faces as pips not as numbers. **\[4\]**
5. When the first player reaches or exceeds the target score, all other players (in a multi-player game) have one final turn to try and beat that score. In this case, the player at the end of the round with the highest score wins. **\[5\]**
6. The basic game includes the minimal scoring options to make the game playable. However, you can include three or more of the following scoring combinations to make the game more interesting. **\[5\]**