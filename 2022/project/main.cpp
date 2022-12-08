/* Main function, calling a specfic function for each advent day */
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include "day1.h"

#define DAY 1



int main() {
    int day_num = DAY;
    std::string filename = "../day" + std::to_string(day_num) + "/input.txt";
    std::ifstream dfile = std::ifstream(filename, std::ios::binary);
    if (dfile.is_open())
    {
        std::cout << "File successfuly opened" << std::endl;
        /* processing goes here */
        day1(dfile);

        /* close the file */
        dfile.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }



}