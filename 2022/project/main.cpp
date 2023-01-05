/* Main function, calling a specfic function for each advent day */
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "day1.h"
#include "day2.h"

#define DAY 2



int main() {
    int day_num = DAY;
    std::string filename = "../day" + std::to_string(day_num) + "/input.txt";
    std::ifstream dfile = std::ifstream(filename, std::ios::binary);
    if (dfile.is_open())
    {
        std::cout << "File successfuly opened" << std::endl;
        /* processing goes here */
        switch (DAY)
        {
            case 1:
            {
                day1(dfile);
                break;
            }
            case 2:
            {
                day2(dfile);
                break;
            }
            default:
                std::cout << "Bad DAY!" << std::endl;
            
        }
        /* close the file */
        dfile.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }



}