#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <array>
#define BOARD_ROWS 5
#define BOARD_COLS 5

class Board
{
public:
    Board();
    Board(const Board &original);
    Board(std::array<std::array<int, BOARD_COLS>, BOARD_ROWS>);
    ~Board();
    int check_for_win();
    int place_number(int number);
    int sum_unmasked();
    //read(std::ifstream input);

private:
    std::array<std::array<int,BOARD_COLS>, BOARD_ROWS> numbers;
    std::array<std::array<int, BOARD_COLS>, BOARD_ROWS> mask;

};



#endif