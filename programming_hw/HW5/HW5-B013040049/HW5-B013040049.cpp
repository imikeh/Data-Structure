#include <iostream>
#include <cstdio>
#include <cstdlib>

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Nov.8,2013*/
/*目的: 進行Ackerman function 之測試*/

using namespace std;

int Ackerman(int m,int n);
int counter;

int main(){

    int m,n;
    counter=0;
    cin >> m >> n ;

    Ackerman(m,n);

    printf("count: %d\n",counter);

    return 0;
}

int Ackerman(int m,int n){
    counter++;
    if(m==0){
            return n+1;
    }
    if(m!=0&&n==0){
            return Ackerman(m-1,1);
    }
    else{
            return Ackerman(m-1,Ackerman(m,n-1));
    }
}






















