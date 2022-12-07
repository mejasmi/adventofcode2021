       #include <fstream>
#include <iostream>
#include <stdio.h>
//#include <vector>
//#include <queue>
#include <array>
#include <math.h>
using namespace std;

#define SLIDING 1
#define FILENAME "../../../input.txt"

//int queue_sum(queue<int> q3)
//{
//    int qsum = 0;
//    while (q3.size() > 0)
//    {
//        qsum = qsum + q3.front();
//        q3.pop();
//    }
//    return qsum;
//}

int main()
{
    ifstream dfile = ifstream(FILENAME, ios_base::in);
    if (dfile.is_open())
    {
        cout << "File successfuly opened" << endl;

        /* processing goes here */
        if (!SLIDING)
        {
            int last_depth = 0;
            int new_depth = 0;
            int num_of_increase = 0;
            dfile >> last_depth;
            while (dfile >> new_depth)
            {
                if (new_depth > last_depth)
                {
                    num_of_increase++;
                }
                last_depth = new_depth;
            }

            cout<<"Number of increases is "<<num_of_increase<<"."<<endl;
        }
        else
        {
            /* Trying out array option and mod indexing*/
            int new_depth = 0;
            int num_of_increase = 0;
            int sum_of_last = 0, sum_of_new = 0;
            size_t depth = 3;
            array<int, 3> last_three = {0,0,0};
            array<int, 3> new_three = {0,0,0};
            for (int i=0; i<3; i++)
            {
                dfile >> new_depth;
                last_three[i] = new_depth;
                sum_of_last = sum_of_last + new_depth;
                new_three[i] = new_depth;
                sum_of_new = sum_of_new + new_depth;
            }
            int mod_cnt = 0;
            while (dfile >> new_depth)
            {
                sum_of_new = sum_of_new - new_three[mod_cnt];
                new_three[mod_cnt] = new_depth;
                sum_of_new = sum_of_new + new_three[mod_cnt];
                if (sum_of_new > sum_of_last)
                {
                    num_of_increase++;
                }
                sum_of_last = sum_of_last - last_three[mod_cnt];
                last_three[mod_cnt] = new_depth;
                sum_of_last = sum_of_last + last_three[mod_cnt];

                mod_cnt = int(fmod(++mod_cnt, 3));
            }
            cout << "Number of sliding increases is " << num_of_increase << "." << endl;

            /* Test drive with <queue> type */
            //int new_depth = 0;
            //int num_of_increase = 0;
            //size_t depth = 3;
            //queue<int> last_three = {};
            //queue<int> new_three = {};
            //while (last_three.size() < depth)
            //{
            //    dfile >> new_depth;
            //    last_three.push(new_depth);
            //    new_three.push(new_depth);
            //}
            //while (dfile >> new_depth)
            //{
            //    new_three.pop();
            //    new_three.push(new_depth);
            //    if (queue_sum(new_three) > queue_sum(last_three))
            //    {
            //        num_of_increase++;
            //    }
            //    last_three.pop();
            //    last_three.push(new_depth);
            //}
            //cout << "Number of sliding increases is " << num_of_increase << "." << endl;

        }
        /* close the file */
        dfile.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }


}

//FILE *dfile;
//
//int main()
//{
//    errno_t err;
//    err = fopen_s(&dfile, FILENAME, "rb");
//    if (err == 0)
//    {
//        std::cout<<"File successfuly opened"<<std::endl;
//
//        /* processing goes here */
//        int last_depth = 0;
//        int new_depth = 0;
//        int num_of_increase = 0;
//        last_depth = _getw(dfile);
//        while (dfile >> new_depth)
//        {
//            if (new_depth > last_depth)
//            {
//                num_of_increase++;
//            }
//            last_depth = new_depth;
//        }
//        
//        /* close the file */
//        err = fclose(dfile);
//        if (err == 0)
//        {
//            printf("The file was closed\n");
//        }
//        else
//        {
//            printf("The file was not closed\n");
//        }
//    }
//    else
//    {
//        std::cout<<"Unable to open file."<<std::endl;
//    }
//
//
//}