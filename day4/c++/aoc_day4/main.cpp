/*
--- Day 4: Giant Squid ---
You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
8  2 23  4 24
21  9 14 16  7
6 10  3 18  5
1 12 20 15 19

3 15  0  2 22
9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
2  0 12  3  7
After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?*/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include <string>
#include <sstream>

#include "board.h"

#define FILENAME "../../input.txt"


int main() {


    std::ifstream dfile = std::ifstream(FILENAME, std::ios::binary);
    if (dfile.is_open())
    {
        std::cout << "File successfuly opened" << std::endl;
        /* processing goes here */

        std::string first_line;
        std::vector<int> picked_numbers;

        if (dfile >> first_line)
        {
            std::istringstream iss1(first_line);
            int number;
            while (iss1 >> number)
            {
                picked_numbers.push_back(number);
                if (iss1.peek() == ',')
                    iss1.ignore();
            }
            
            // read the boards into a vector
            //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(dfile), {});

            int num_of_board = 0;
            std::vector<int> boards_still_in_play;
            
            // since thetotal number of boards is unknown we place them in a vector
            // board size is known and expected to be 5x5
            std::vector<Board> boards;

            int temp_num = 0;

            int curr_row=0, curr_col = 0;
            std::array<std::array<int, BOARD_COLS>, BOARD_ROWS> curr_numbers;

            while (dfile >> temp_num)
            {
                curr_numbers[curr_row][curr_col] = temp_num;
                
                curr_col++;

                if (curr_col >= BOARD_COLS)
                {
                    curr_col = 0;
                    curr_row++;

                    if (curr_row >= BOARD_ROWS)
                    {
                        curr_row = 0;
                        boards_still_in_play.push_back(int(boards.size()));
                        Board curr_board(curr_numbers);
                        boards.push_back(curr_board);
                        
                    }
                }
            }

            /* HERE COMES PROCESSING */

            int final_result = 0;
            bool bingo = false;
            int winner_board_id = 0;

            // part two - loser board
            int loser_result = 0;
            int loser_board_id = 0;
            bool loser_found = false;
            std::vector<int> done_boards;

            for (int pnum = 0; pnum < picked_numbers.size(); pnum++)
            {
                std::vector<int> boards_remained;
                // for each new picked number mask it in the board, and chech if there is a win
                for (int bnum = 0; bnum < boards_still_in_play.size(); bnum++)
                {   
                    
                    if (boards[boards_still_in_play[bnum]].place_number(picked_numbers[pnum]))
                    {
                        if (boards[boards_still_in_play[bnum]].check_for_win())
                        {
                            if (!bingo)
                            {
                                final_result = boards[boards_still_in_play[bnum]].sum_unmasked() * picked_numbers[pnum];
                                winner_board_id = boards_still_in_play[bnum];
                                bingo = true;
                            }
                            done_boards.push_back(boards_still_in_play[bnum]);
                            if (done_boards.size() == boards.size())
                            {
                                loser_result = boards[boards_still_in_play[bnum]].sum_unmasked() * picked_numbers[pnum];
                                loser_board_id = boards_still_in_play[bnum];
                                loser_found = true;
                                break;
                            }
                        }
                        else
                        {
                            boards_remained.push_back(boards_still_in_play[bnum]);
                        }
                    }
                    else
                    {
                        boards_remained.push_back(boards_still_in_play[bnum]);
                    }
                }
                boards_still_in_play.empty();
                boards_still_in_play = boards_remained;
                if (loser_found)
                {
                    break;
                }
            }
            
            std::cout << "Final score is: " << final_result << ",and the winner board is "<< winner_board_id << "." << std::endl;
            std::cout << "Loser score is: " << loser_result << ",and the loser board is " << loser_board_id << "." << std::endl;
                }
        else
        {
            std::cout << "File could not be read." << std::endl;
        }

        /* close the file */
        dfile.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }



}