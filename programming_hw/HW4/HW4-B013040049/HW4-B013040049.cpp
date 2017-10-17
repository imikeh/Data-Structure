#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Oct.30,2013*/
/*目的: 用recursion撰寫一個程式來記錄一個n*n的西洋棋中棋子所經過路徑的順序*/

using namespace std;

int n;
int k[8][2] = { {-2,1} , {-1,2} , {1,2} , {2,1} , {2,-1} , {1,-2} , {-1,-2} , {-2,-1} }; /*8種方位*/
int cb[10][10];/*cheese board棋盤*/

int knight(int,int,int); /*利用int型態fuction，若有解則回傳1，無解則回傳0*/

int main()
{
    int i,j;
    for(n=1;n<=6;n++)
    {
        int x=1,y=1,num=0; /*每次都要重新設定一次x,y座標，num為座標的數字*/
        for(i=1;i<n+1;i++){ /*陣列歸0*/
            for(int j=1 ; j<n+1 ; j++){
                cb[i][j] = 0;
            }
        }

        cb[x][y] = num = num+1; /*棋盤啟點*/

        if(!knight(x,y,num+1)){ /*若回傳值為0則沒有答案*/
            cout << "No solution" << endl;
        }
        else{ /*若回傳值為1則有答案*/
            for(i=1;i<=n;i++){
                for(j=1;j<=n;j++){
                    printf("%3d",cb[i][j]); /*改用%3d方式來印出數字*/
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
            return 1; /*有解回傳1*/
    }
    if(num==1){
            return 0; /*無解回傳0*/
    }

    for(i=0;i<8;i++){ /*八個方位*/
        int xx = k[i][0] + x; /*下一個x座標*/
        int yy = k[i][1] + y; /*下一個y座標*/
        if(cb[xx][yy] == 0 && xx >= 1 && yy >=1 && xx <=n && yy <=n){
                cb[xx][yy] = num; /*填入數字*/
            if(knight(xx,yy,num+1)){ /*找下一個方位*/
                return 1;
            }
        }

    }
    cb[x][y] = 0; /*歸零*/
    return 0;
}





