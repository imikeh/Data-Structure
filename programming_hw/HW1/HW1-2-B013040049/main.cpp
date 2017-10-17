#include <iostream>
using namespace std;

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Sep.28,2013*/
/*目的: OOP Homework 1-2*/

int main()
{
    int T, O, G, D; /*設定所要的數字*/

    for (T = 0; T < 10; T++) /*利用迴圈當相同的時候輸出*/
    {
        for (O = 0; O < 10; O++)
        {
            for (G = 0; G < 10; G++)
            {
                for (D = 0; D < 10; D++)
                {
                    if ((D == G) || (D == O) || (D == T) || (G == O) || (G == T) || (O == T))
                        continue;
                    else if (400 * T + 40 * O + 4 * O == 1000 * G + 100 * O + 10 * O + D) /*檢測是否相同*/
                    {
                        cout  << "T = " << T /*輸出*/
                              << ", O = " << O
                              << ", G = " << G
                              << ", D = " << D << endl;
                        break;
                    }
                }

            }
        }
    }
    return 0;
}
