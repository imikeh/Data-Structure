#include<stdio.h>

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Sep.28,2013*/
/*目的: 魔方陣*/

int main()
{
int m[10][10]={{0}}; /*假設一個二維陣列*/

int a,i,b; /*迴圈變數*/
int x; /*幾階*/
int n; /*數字1位置*/

for(x=1;x<10;x=x+2){ /*x為幾階的意思*/

a=1;

n=(x+1)/2; /*n為數字1的位置*/

for(i=1;i<=x*x;i++){
	if(a==0){
		a=x;
	}
    if(n==x+1){
		n=1;
	}

m[a][n]=i; /*i為目前要輸入的數字把它存進二維陣列*/
a = a - 1;
n = n + 1;

    if(i%(x)==0){
		a = a + 2;
		n = n - 1;
	}
}

for(i=1;i<=x;i++){
	for(b=1;b<=x;b++){
		printf("%4d",m[i][b]); /*用二維陣列搭配兩層迴圈跑出答案*/
	}
	printf("\n");
}

printf("\n");

}
return 0;
}


