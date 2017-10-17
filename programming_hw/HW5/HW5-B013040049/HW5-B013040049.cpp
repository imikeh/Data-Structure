#include <iostream>
#include <cstdio>
#include <cstdlib>

/*�@�̩m�W: B013040049 ����*/
/*���g���: Nov.8,2013*/
/*�ت�: �i��Ackerman function ������*/

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






















