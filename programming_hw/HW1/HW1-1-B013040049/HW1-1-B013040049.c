#include<stdio.h>

/*�@�̩m�W: B013040049 ����*/
/*���g���: Sep.28,2013*/
/*�ت�: �]��}*/

int main()
{
int m[10][10]={{0}}; /*���]�@�ӤG���}�C*/

int a,i,b; /*�j���ܼ�*/
int x; /*�X��*/
int n; /*�Ʀr1��m*/

for(x=1;x<10;x=x+2){ /*x���X�����N��*/

a=1;

n=(x+1)/2; /*n���Ʀr1����m*/

for(i=1;i<=x*x;i++){
	if(a==0){
		a=x;
	}
    if(n==x+1){
		n=1;
	}

m[a][n]=i; /*i���ثe�n��J���Ʀr�⥦�s�i�G���}�C*/
a = a - 1;
n = n + 1;

    if(i%(x)==0){
		a = a + 2;
		n = n - 1;
	}
}

for(i=1;i<=x;i++){
	for(b=1;b<=x;b++){
		printf("%4d",m[i][b]); /*�ΤG���}�C�f�t��h�j��]�X����*/
	}
	printf("\n");
}

printf("\n");

}
return 0;
}


