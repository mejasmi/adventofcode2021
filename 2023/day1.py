"""
The newly-improved calibration document consists of lines of text; 
each line originally contained a specific calibration value that the Elves now need to recover. 
On each line, the calibration value can be found by combining 
the first digit and the last digit (in that order) to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
In this example, the calibration values of these four lines are 12, 38, 15, and 77. 
Adding these together produces 142.

Consider your entire calibration document. What is the sum of all of the calibration values?
"""

"""
Your puzzle answer was 54708.
"""

"""
--- Part Two ---
Your calculation isn't quite right. 
It looks like some of the digits are actually spelled out with letters:
 one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and last digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.

What is the sum of all of the calibration values?
"""


import numpy as np
import re

file_path = "data/input_day1.txt"

DIGITS = ['0','1','2','3','4','5','6','7','8','9']
WRITTEN_DIGITS = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
WRITTEN_VALUES = {'one':1, 'two':2, 'three':3, 'four':4, 'five':5, 'six':6, 'seven':7, 'eight':8, 'nine':9}
def is_int(s):
    try: 
        int(s)
    except ValueError:
        return False
    else:
        return True

def extract_numbers(text_line: str):
    first_digit = None
    curr_digit = None
    for ch in text_line:
        if is_int(ch):
            if first_digit == None:
                first_digit = int(ch)
            curr_digit = int(ch)
    return 10*first_digit+curr_digit

def extract_numbers2(text_line: str):
    all_digits = set(DIGITS).union(set(WRITTEN_DIGITS))
    positions_dict = {dig: None for dig in all_digits}
    for digit in all_digits:
        positions_dict[digit] = [m.start() for m in re.finditer(digit, text_line)]
    # Find the key with the lowest position
    min_key = min(positions_dict, key=lambda k: min(positions_dict[k]) if positions_dict[k]!=[] else np.inf)
    if min_key in WRITTEN_DIGITS:
        first_digit = WRITTEN_VALUES[min_key]
    else:
        first_digit = int(min_key)
    # Find the key with the highest position
    max_key = max(positions_dict, key=lambda k: max(positions_dict[k]) if positions_dict[k]!=[] else -1)
    if max_key in WRITTEN_DIGITS:
        last_digit = WRITTEN_VALUES[max_key]
    else:
        last_digit = int(max_key)
    return 10*first_digit + last_digit
    

with open(file=file_path, mode="r+") as file:
    lines = file.readlines()
    coordinates = []
    for line in lines:
        coordinates.append(extract_numbers2(line))

print(np.sum(np.array(coordinates)))