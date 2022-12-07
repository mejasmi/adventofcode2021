/*
--- Day 3: Binary Diagnostic ---
The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.

The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.

You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010
Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.

The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.

The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

Your puzzle answer was 741950.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---
Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
If you only have one number left, stop; this is the rating value for which you are searching.
Otherwise, repeat the process, considering the next bit to the right.
The bit criteria depends on which type of rating value you want to find:

To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.
For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
Then, to determine the CO2 scrubber rating value from the same example above:

Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)*/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <array>
#include <math.h>

#define FILENAME "../../input.txt"

int main() {


    std::ifstream dfile = std::ifstream(FILENAME, std::ios::binary);
    if (dfile.is_open())
    {
        std::cout << "File successfuly opened" << std::endl;
        /* processing goes here */
        int num_of_bits = 0;
        int num_of_lines = 0;

        // read the whole file into a vector
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(dfile), {});

        
        int k=0;
        while (buffer[k] != '\n')
        {
            k++;
        }
        num_of_bits = k;

        num_of_lines = int(buffer.size()/(num_of_bits+1));

        std::vector<std::vector<int>> bit_matrix;
        for (int i = 0; i < num_of_lines; i++)
        {
            std::vector<int> row = {};
            for (int j = 0; j < num_of_bits; j++)
            {
                // every row has num_of_bits + 1 chars (bc '\n')
                // value is converted from uchar to int
                row.push_back(buffer[i*(num_of_bits+1) + j] - '0');
            }
            bit_matrix.push_back(row);
        }


        // extract most common values for gamma and epsilon rate
        std::string s_gamma_rate, s_epsilon_rate;
        int gamma_rate = 0, epsilon_rate=0;

        std::vector<int> total;
        for (int i = 0; i < num_of_bits; i++)
        {
            total.push_back(0);
        }
        for (int i = 0; i < num_of_lines; i++)
        {
            for (int j = 0; j < num_of_bits; j++)
            {
                total[j] = total[j] + bit_matrix[i][j];
            }
        }

        for (int i = 0; i < num_of_bits; i++)
        {
            if (total[i] * 2 > num_of_lines)
            {
                s_gamma_rate.push_back('1');
                gamma_rate = gamma_rate + int(std::exp2(num_of_bits-i-1));
                s_epsilon_rate.push_back('0');
            }
            else
            {
                s_gamma_rate.push_back('0');
                s_epsilon_rate.push_back('1');
                epsilon_rate = epsilon_rate + int(std::exp2(num_of_bits - i - 1));
            }
        }
        std::cout << "Consumption is: " << gamma_rate*epsilon_rate << "." << std::endl;

        /* PART TWO */
        /* oxygen generator rating & C02 scrubber rating*/
        int oxy_rate = 0, c02_rate = 0;

        std::vector<int> next_id;

        // fill the fist list of line indices with values from 0 to 999
        for (int i = 0; i < num_of_lines; i++)
        {
            next_id.push_back(i);
        }

        for (int j = 0; j < num_of_bits; j++)
        {
            int total_ones = 0, total_zeros = 0;
            std::vector<int> ones_id = {};
            std::vector<int> zeros_id = {};
            for (unsigned int i = 0; i < next_id.size(); i++)
            {
                if (bit_matrix[next_id[i]][j] == 1)
                {
                    total_ones++;
                    ones_id.push_back(next_id[i]);
                }
                else if (bit_matrix[next_id[i]][j] == 0)
                {
                    total_zeros++;
                    zeros_id.push_back(next_id[i]);
                }

            }
            if (total_ones+total_zeros>1)
            {
                next_id.clear();
                if (total_zeros > total_ones)
                {
                    next_id = zeros_id;
                }
                else
                {
                    next_id = ones_id;
                    oxy_rate = oxy_rate + int(std::exp2(num_of_bits-1-j));
                }
            }
            else
            {
                oxy_rate = oxy_rate + int(std::exp2(num_of_bits - 1 - j))*bit_matrix[next_id[0]][j];
            }
        }

        // fill the fist list of line indices with values from 0 to 999
        next_id.clear();
        for (int i = 0; i < num_of_lines; i++)
        {
            next_id.push_back(i);
        }

        for (int j = 0; j < num_of_bits; j++)
        {
            int total_ones = 0, total_zeros = 0;
            std::vector<int> ones_id = {};
            std::vector<int> zeros_id = {};
            for (unsigned int i = 0; i < next_id.size(); i++)
            {
                if (bit_matrix[next_id[i]][j] == 1)
                {
                    total_ones++;
                    ones_id.push_back(next_id[i]);
                }
                else if (bit_matrix[next_id[i]][j] == 0)
                {
                    total_zeros++;
                    zeros_id.push_back(next_id[i]);
                }

            }
            
            if (total_zeros + total_ones > 1)
            {
                next_id.clear();
                if (total_zeros > total_ones)
                {
                    next_id = ones_id;
                    c02_rate = c02_rate + int(std::exp2(num_of_bits - 1 - j));
                
                }
                else
                {
                    next_id = zeros_id;
                }
            }
            // if there is only one item left, add the remaining digits and break
            else
            {
                c02_rate = c02_rate + int(std::exp2(num_of_bits - 1 - j))*bit_matrix[next_id[0]][j];
            }
            

        }



        std::cout << "Life support rating is: " << oxy_rate*c02_rate << "." << std::endl;



        /* close the file */
        dfile.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }



}