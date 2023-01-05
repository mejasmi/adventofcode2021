/*
--- Day 2: Rock Paper Scissors ---
The Elves begin to set up camp on the beach. To decide whose tent gets to be closest to the snack storage, a giant Rock Paper Scissors tournament is already in progress.

Rock Paper Scissors is a game between two players. Each game contains many rounds; in each round, the players each simultaneously choose one of Rock, Paper, or Scissors using a hand shape. Then, a winner for that round is selected: Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. If both players choose the same shape, the round instead ends in a draw.

Appreciative of your help yesterday, one Elf gives you an encrypted strategy guide (your puzzle input) that they say will be sure to help you win. "The first column is what your opponent is going to play: A for Rock, B for Paper, and C for Scissors. The second column--" Suddenly, the Elf is called away to help with someone's tent.

The second column, you reason, must be what you should play in response: X for Rock, Y for Paper, and Z for Scissors. Winning every time would be suspicious, so the responses must have been carefully chosen.

The winner of the whole tournament is the player with the highest score. Your total score is the sum of your scores for each round. The score for a single round is the score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).

Since you can't be sure if the Elf is trying to help you or trick you, you should calculate the score you would get if you were to follow the strategy guide.

For example, suppose you were given the following strategy guide:

A Y
B X
C Z
This strategy guide predicts and recommends the following:

In the first round, your opponent will choose Rock (A), and you should choose Paper (Y). This ends in a win for you with a score of 8 (2 because you chose Paper + 6 because you won).
In the second round, your opponent will choose Paper (B), and you should choose Rock (X). This ends in a loss for you with a score of 1 (1 + 0).
The third round is a draw with both players choosing Scissors, giving you a score of 3 + 3 = 6.
In this example, if you were to follow the strategy guide, you would get a total score of 15 (8 + 1 + 6).

What would your total score be if everything goes exactly according to your strategy guide?

Your puzzle answer was 10595.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---
The Elf finishes helping with the tent and sneaks back over to you. "Anyway, the second column says how the round needs to end: X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win. Good luck!"

The total score is still calculated in the same way, but now you need to figure out what shape to choose so the round ends as indicated. The example above now goes like this:

In the first round, your opponent will choose Rock (A), and you need the round to end in a draw (Y), so you also choose Rock. This gives you a score of 1 + 3 = 4.
In the second round, your opponent will choose Paper (B), and you choose Rock so you lose (X) with a score of 1 + 0 = 1.
In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = 7.
Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of 12.

Following the Elf's instructions for the second column, what would your total score be if everything goes exactly according to your strategy guide?*/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <math.h>

enum rps_values{Rock = 1, Paper = 2, Scissors=3};
enum ABC_values{A=1, B=2, C=3};
enum XYZ_values{X=1, Y=2, Z=3};
enum state{loss=0, draw=3, win=6};


void day2(std::ifstream &dfile) {
    /* processing goes here */

    std::string file_line;
    int total_score = 0;
    int total_score2 = 0;
    ABC_values abc_value;
    XYZ_values xyz_value;
    while (std::getline(dfile, file_line))
    {
        state result;
        switch (file_line[0])
        {
            case 'A':
            {
                abc_value = A;
                break;
            }
            case 'B':
            {
                abc_value =B;
                break;
            }
            case 'C':
            {
                abc_value = C;
                break;
            }
            default:
                std::cout << "Invalid first char." << std::endl;
        }

        switch (file_line[2])
        {
            case 'X':
            {
                xyz_value = X;
                break;
            }
            case 'Y':
            {
                xyz_value = Y;
                break;
            }
            case 'Z':
            {
                xyz_value = Z;
                break;
            }
            default:
                std::cout << "Invalid second char." << std::endl;
        }

        /* PART 1 - X, Y, Z understood as paly moves ROCK, PAPER, SCISSORS*/
        if (abc_value == xyz_value)
        {
            //draw
            result = draw;
        }
        else if ((abc_value - (xyz_value % 3)) == 1)
        {
            // loss
            result = loss;
        }
        else
        {
            // win
            result = win;
        }
        total_score += xyz_value + result;
        
        /* PART 2 - X, Y, Z understood as play results LOSE, DRAW, WIN */
        switch (file_line[2])
        {
            case 'X':
            {   
                result = loss;
                xyz_value = abc_value != 1 ? XYZ_values(abc_value - 1) : XYZ_values(3);
                break;
            }
            case 'Y':
            {
                result = draw;
                xyz_value = XYZ_values(abc_value);
                break;
            }
            case 'Z':
            {
                result = win;
                xyz_value = abc_value != 3 ? XYZ_values(abc_value+1) : XYZ_values(1);
                break;
            }
            default:
                std::cout << "Invalid second char." << std::endl;
        }
        total_score2 += xyz_value + result;

    }

    std::cout << "Final score is: " << total_score << "." << std::endl;

    
    
    std::cout << "Final score 2 is: " << total_score2 << "." << std::endl;

    return;
}