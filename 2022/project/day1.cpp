/*
The jungle must be too overgrown and difficult to navigate in vehicles or access from the air; the Elves' expedition traditionally goes on foot. As your boats approach land, the Elves begin taking inventory of their supplies. One important consideration is food - in particular, the number of Calories each Elf is carrying (your puzzle input).

The Elves take turns writing down the number of Calories contained by the various meals, snacks, rations, etc. that they've brought with them, one item per line. Each Elf separates their own inventory from the previous Elf's inventory (if any) by a blank line.

For example, suppose the Elves finish writing their items' Calories and end up with the following list:

1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
This list represents the Calories of the food carried by five Elves:

The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total of 6000 Calories.
The second Elf is carrying one food item with 4000 Calories.
The third Elf is carrying food with 5000 and 6000 Calories, a total of 11000 Calories.
The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a total of 24000 Calories.
The fifth Elf is carrying one food item with 10000 Calories.
In case the Elves get hungry and need extra snacks, they need to know which Elf to ask: they'd like to know how many Calories are being carried by the Elf carrying the most Calories. In the example above, this is 24000 (carried by the fourth Elf).

Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?

Your puzzle answer was 70720.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---
By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories of food might eventually run out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three Elves carrying the most Calories. That way, even if one of those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with 10000 Calories). The sum of the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?*/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

void day1(std::ifstream &dfile) {
    /* processing goes here */

    std::string file_line;
    int calorie_number = 0;
    int cal_sum = 0;
    int winner_elf;
    std::vector<int> elf_calories;
    // vector of int vectors, list of calories for each elf.
    std::vector<std::vector<int>> calories;
    std::vector<int> cal_sum_per_elf;

    while (std::getline(dfile, file_line))
    {
        if (file_line != "")
        {
            // while there are numbers on lines
            // place them in vector and sum them
            calorie_number = std::stoi(file_line);
            elf_calories.push_back(calorie_number);
            cal_sum += calorie_number;
        }
        else
        {
            calories.push_back(elf_calories);
            elf_calories.empty();
            cal_sum_per_elf.push_back(cal_sum);
            cal_sum = 0;
        }
    }

    cal_sum = *std::max_element(cal_sum_per_elf.begin(), cal_sum_per_elf.end());
    auto it = find(cal_sum_per_elf.begin(), cal_sum_per_elf.end(), cal_sum);
    winner_elf = it - cal_sum_per_elf.begin();
    std::cout << "Hightest calorie number is: " << cal_sum << ",and the winner elf is " << winner_elf << "." << std::endl;

    /* SECOND PART */
    // sort in descending order
    std::sort(cal_sum_per_elf.begin(), cal_sum_per_elf.end(), std::greater<int>());

    int top_three = cal_sum_per_elf[0] + cal_sum_per_elf[1] + cal_sum_per_elf[2];

    std::cout << "Top three elfs' calorie number is: " << top_three << "." << std::endl;
    // 207148 final answer
    return;
}