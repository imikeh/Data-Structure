#include <stdio.h>

/*�@�̩m�W: B013040049 ����*/
/*���g���: Sep.29,2013*/
/*�ت�: �L�X����1��50�����Ҧ��Ƥ����h*/

int main()
{

int m,carry,i,j,x,k,y; /*m����J�����h�ơAcarry���x�s�i��ơA��L���ܼ�*/
int a[1000]={0}; /*�x�s���X���}�C*/

while(scanf("%d",&m)!=0){
if(m==0){
        break; /*�Y��J�O0�h�j����X*/
}
else{
    a[0]=1; /*��l��a[0]*/
for(i=1;i<=m;i++){
    for(j=0;j<1000;j++){
        a[j]=a[j]*i;
    }
    for(j=0;j<1000;j++){
        carry=a[j]/10; /*��Ʀr���H10�A�]���o�̬Oint�ҥH�ұo��Ʀr���i��Ʀr*/
        a[j]=a[j]%10; /*�D���H10���l�ƥi�o��D�i��Ʀr*/
        a[j+1]=a[j+1]+carry; /*��U�@�ӼƦr�[�W�e���ұo�i���*/
    }
    for(j=999;j>=0;j--){ /*�p�����*/
        if(a[j]!=0){ /*�Q�Χ�줣����0�ӧ����*/
            k=j;
            break;
        }
    }
    printf("%d ! = ",i);
    for(j=k;j>=0;j--){
        printf("%d",a[j]); /*�����׫�q�Y�L���*/
    }
    printf("\n");
}
    for(j=0;j<=1000;j++){ /*�Q�ΰj����array�k�s*/
        a[j]=0;
}
}
printf("\n");
}
    return 0;
}
