#include "board.h"
#include <array>
#include <algorithm>

Board::Board()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        numbers[i].fill(0);
        mask[i].fill(0);
    }
}

Board::~Board()
{
    numbers.empty();
    mask.empty();
}

Board::Board(const Board &original)
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            numbers[i][j] = original.numbers[i][j];
            mask[i][j] = original.mask[i][j];
        }
    }
}

Board::Board(std::array<std::array<int, BOARD_COLS>, BOARD_ROWS> values)
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            numbers[i][j] = values[i][j];
        }
        mask[i].fill(0);
    }
}

/**@brief check_for_win
function checking if there is a win on a board
Mask matrix values are summed by columns and rows.
If the maximum value in row/column sums is larger than the
number of rows/columns there is a win.
@return - integer value 1 - bingo, 0 - no bingo yet.
*/
int Board::check_for_win()
{
    std::array<int, BOARD_ROWS> row_sum;
    std::array<int, BOARD_COLS> col_sum;
    row_sum.fill(0);
    col_sum.fill(0);
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            row_sum[i] += mask[i][j];
            col_sum[j] += mask[i][j];
        }
    }
    std::array<int, BOARD_ROWS>::iterator max_row_elem;
    std::array<int, BOARD_COLS>::iterator max_col_elem;
    max_row_elem = std::max_element(row_sum.begin(), row_sum.end());
    max_col_elem = std::max_element(col_sum.begin(), col_sum.end());
    if ((*max_row_elem < BOARD_ROWS) && (*max_col_elem < BOARD_COLS))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/**@brief place_number
function checking if there is a match for the current picked number
For each board row, a check is performed to find the provided number.
If found, the position of the number is masked, and function returns 1.
If the whole board is searched with no match, function returns 0.
Only one hit is expected, there should not be duplicate numbers.
@ param number - input number for which the board is searched
@return - integer value 1 - number was found, 0 - no match on this board.
*/
int Board::place_number(int number)
{
    // checking for the number in each row
    std::array<int,BOARD_COLS>::iterator number_found;
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        number_found = std::find(this->numbers[i].begin(), this->numbers[i].end(), number);
        if (number_found != this->numbers[i].end())
        {
            // mask the found number
            this->mask[i][std::distance(this->numbers[i].begin(), number_found)] = 1;
            // since we expect only one number to be found we can exit
            return 1;
        }
    }
    return 0;
}

/**@brief sum_unmasked
function performs summation of all unmasked values in the board.
The board values are iterated through and all numbers that are unmasked are summed.
Mask is used to decide if the number is added to the sum.
@return - sum of all unmaksed values.
*/
int Board::sum_unmasked()
{
    int sum = 0;
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            sum += this->mask[i][j] ? 0 : this->numbers[i][j];
        }
    }
    return sum;
}