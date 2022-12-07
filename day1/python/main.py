"""
As the submarine drops below the surface of the ocean, it automatically performs a sonar sweep of the nearby sea floor. On a small screen, the sonar sweep report (your puzzle input) appears: each line is a measurement of the sea floor depth as the sweep looks further and further away from the submarine.

For example, suppose you had the following report:

199
200
208
210
200
207
240
269
260
263
This report indicates that, scanning outward from the submarine, the sonar sweep found depths of 199, 200, 208, 210, and so on.

The first order of business is to figure out how quickly the depth increases, just so you know what you're dealing with - you never know if the keys will get carried into deeper water by an ocean current or a fish or something.

To do this, count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) In the example above, the changes are as follows:

199 (N/A - no previous measurement)
200 (increased)
208 (increased)
210 (increased)
200 (decreased)
207 (increased)
240 (increased)
269 (increased)
260 (decreased)
263 (increased)
In this example, there are 7 measurements that are larger than the previous measurement.

How many measurements are larger than the previous measurement?
"""

# Advent of code
# DAY 1
# created by mejasmi
# created on:   14.11.2022.
# last edit:    14.11.2022.

import numpy as np

def main(dfile, sliding):

    num_of_increase = 0
    if (not sliding):
        last_depth = int(next(dfile))
        for line in dfile:
            new_depth = int(line)
            if (new_depth > last_depth):
                num_of_increase = num_of_increase + 1
            last_depth = new_depth


        # last_depth = 0
        # num_of_increase = 0
        # skip_first = True
        # for line in dfile:
        #     new_depth = int(line)
        #     if skip_first:
        #         skip_first = False
        #         last_depth = new_depth
        #         continue
        #     if (new_depth > last_depth):
        #         num_of_increase = num_of_increase + 1
        #     last_depth = new_depth
    
    else:
        last_three = []
        new_three = []
        while (len(last_three) < 3):
            new_depth = int(next(dfile))
            last_three.append(new_depth)
            new_three.append(new_depth)

        for line in dfile:
            new_depth = int(line)
            new_three.pop(0)
            new_three.append(new_depth)
            if (sum(new_three) > sum(last_three)):
                num_of_increase = num_of_increase + 1
            last_three.pop(0)
            last_three.append(new_depth)


    return num_of_increase


if __name__ == '__main__':
    # open the input file
    dfile = open("../input.txt", "r")
    result = main(dfile=dfile, sliding=True)
    print("Number of increases is %d.\n" % result)

