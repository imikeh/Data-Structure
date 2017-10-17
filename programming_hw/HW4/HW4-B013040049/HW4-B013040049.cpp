#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>

/*�@�̩m�W: B013040049 ����*/
/*���g���: Oct.30,2013*/
/*�ت�: ��recursion���g�@�ӵ{���ӰO���@��n*n����v�Ѥ��Ѥl�Ҹg�L���|������*/

using namespace std;

int n;
int k[8][2] = { {-2,1} , {-1,2} , {1,2} , {2,1} , {2,-1} , {1,-2} , {-1,-2} , {-2,-1} }; /*8�ؤ��*/
int cb[10][10];/*cheese board�ѽL*/

int knight(int,int,int); /*�Q��int���Afuction�A�Y���ѫh�^��1�A�L�ѫh�^��0*/

int main()
{
    int i,j;
    for(n=1;n<=6;n++)
    {
        int x=1,y=1,num=0; /*�C�����n���s�]�w�@��x,y�y�СAnum���y�Ъ��Ʀr*/
        for(i=1;i<n+1;i++){ /*�}�C�k0*/
            for(int j=1 ; j<n+1 ; j++){
                cb[i][j] = 0;
            }
        }

        cb[x][y] = num = num+1; /*�ѽL���I*/

        if(!knight(x,y,num+1)){ /*�Y�^�ǭȬ�0�h�S������*/
            cout << "No solution" << endl;
        }
        else{ /*�Y�^�ǭȬ�1�h������*/
            for(i=1;i<=n;i++){
                for(j=1;j<=n;j++){
                    printf("%3d",cb[i][j]); /*���%3d�覡�ӦL�X�Ʀr*/
                }
                cout << endl;
            }
        cout << " Has a solution" << endl;
        }
        cout << endl;
    }
    return 0;
}


int knight(int x,int y,int num){

    int i;

    if(num>=n*n+1){
            return 1; /*���Ѧ^��1*/
    }
    if(num==1){
            return 0; /*�L�Ѧ^��0*/
    }

    for(i=0;i<8;i++){ /*�K�Ӥ��*/
        int xx = k[i][0] + x; /*�U�@��x�y��*/
        int yy = k[i][1] + y; /*�U�@��y�y��*/
        if(cb[xx][yy] == 0 && xx >= 1 && yy >=1 && xx <=n && yy <=n){
                cb[xx][yy] = num; /*��J�Ʀr*/
            if(knight(xx,yy,num+1)){ /*��U�@�Ӥ��*/
                return 1;
            }
        }

    }
    cb[x][y] = 0; /*�k�s*/
    return 0;
}





