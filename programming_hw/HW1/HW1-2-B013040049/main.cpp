#include <iostream>
using namespace std;

/*�@�̩m�W: B013040049 ����*/
/*���g���: Sep.28,2013*/
/*�ت�: OOP Homework 1-2*/

int main()
{
    int T, O, G, D; /*�]�w�ҭn���Ʀr*/

    for (T = 0; T < 10; T++) /*�Q�ΰj���ۦP���ɭԿ�X*/
    {
        for (O = 0; O < 10; O++)
        {
            for (G = 0; G < 10; G++)
            {
                for (D = 0; D < 10; D++)
                {
                    if ((D == G) || (D == O) || (D == T) || (G == O) || (G == T) || (O == T))
                        continue;
                    else if (400 * T + 40 * O + 4 * O == 1000 * G + 100 * O + 10 * O + D) /*�˴��O�_�ۦP*/
                    {
                        cout  << "T = " << T /*��X*/
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
