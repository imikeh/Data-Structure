#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>

using namespace std;

/*�@�̩m�W: B013040049 ����*/
/*���g���: Oct.25,2013*/
/*�ت�: ���g�@�ӵ{���ӰO���@��n*n����v�Ѥ��Ѥl�Ҹg�L���|������*/


int knight(class stack*,int); /*�Q��int���Afuction�A�Y���ѫh�^��1�A�L�ѫh�^��0*/
void push(class stack*,int,int,int); /*���Jstack*/
void pop(class stack*); /*���Xstack*/
void print(class stack*);

class stack
{
    public:
    int i,j,k;
    class stack *nextptr; /*stack�U�@�Ӫ�����*/
};

int main(void)
{
      class stack S;
      S.nextptr=NULL;
      int n;
      for(n=1;n<=6;n++){ /*�D�حn�Dn=1��n=6*/
            if(n==1){
                cout << " n = " << n << endl;
                cout<< " 1 " << endl;
                }
                else{
                        cout << " n = " << n << endl;
                        if(knight(&S,n)==0){ /*�Y�^�ǭȬ�0�h�S������*/
                                cout <<" No solution "<< endl;
                        }
                        else{ /*�Y�^�ǭȬ�1�h������*/
                                cout <<" Has a solution"<< endl;
                        }
                }
                while((S.nextptr)!= NULL){
                pop((&S));
                }
      }
return 0;
}

int knight(class stack *head,int n)
{
     int c=0,step=1,x=1,i,j,a,b; /*i,j�N��}�C�̪��C�P��, step��ܨ�������*/
     int array[n+1][n+1];
     int k[10][2]={{0,0},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{0,0}}; /*�ŧik����� 0�M9�O{0,0}*/

     for(i=1;i<=n;i++){ /*�Q�Ψ�h�j�������������k0 */
         for(j=1;j<=n;j++){
              array[i][j]=0;
         }
     }

     i = 1;
     j = 1;

     array[i][j]=step; /*step�q1�}�l�A�M��s�J{1,1}�o�Ӧ�}*/
     push(head,i,j,3);

     start:
     for(x=c;x<=9;x++)
     {
          i = i + k[x][0];
          j = j + k[x][1];
          if(x==9){ /*�Y��k9��ܤK�Ӥ�쳣�L�k�e�i�A�ҥH�h�^�W�@�ӵ��G*/
              array[head -> nextptr -> i][head -> nextptr -> j]=0; /*�Q�Ϋ��бN���檺�B�J�k0*/
              c = head -> nextptr -> k + 1; /*c��pop���e�����A+1�A�]���n���U�@�Ӥ��*/
              pop(head); /*�Nstack�̤W�h���X*/
              step = step -1;
          if(i==1&&j==1){ /*�Yk=9�Ai�Pj���O�^���l��m�N��L�ѫh�^��0*/
              return 0;
          }
          i = head -> nextptr -> i; /*i�Pj��pop���᪺stack���̤W�h*/
          j = head -> nextptr -> j;
          goto start; /*�q�s�����c�}�l�]�j��*/
          }
          else if(i<1 || i>n || j<1|| j>n || array[i][j]!=0){ /*�Yi�Pj�W�X�}�C�άO�p��}�C�h���]�j��A���@�Ӥ�V*/
              i = i - k[x][0];
              j = j - k[x][1];
              continue;
          }
          else{ /*�N�����i���A�ҥHstep+1�åBpush���U��i,j����m�P���*/
              step = step +1;
              push(head,i,j,x);
              array[i][j] = step;
              c = 0;
              x = 0; /*�Nx,c�k0�A�q��Vk0�}�l�~��]�j��*/
          }
          if(step==n*n){ /*�Y�i��Fn*n�N��i�H����̫�@�B�A�ҥH���Ѧ^��1�A�æL�X�}�C*/
              for(a=1;a<=n;a++){
                    for(b=1;b<=n;b++){
                        cout << setw(4) << right << array[a][b]; /*�L�X�}�C*/
              }
              cout << endl;
              }
          return 1;
          }
     }
     free(head);
     return 0;
}
void push(class stack *head,int i,int j,int k)
{
     class stack *newnew;

     newnew=(stack*)malloc(sizeof(stack));
     newnew -> nextptr = NULL;
     newnew -> i = i;
     newnew -> j = j;
     newnew -> k = k;
     if(head -> nextptr == NULL){
          head -> nextptr = newnew;
     }
     else{
            newnew -> nextptr = head -> nextptr;
            head -> nextptr = newnew;
            }
}
void pop(class stack *head)
{
     class stack *temp;
     temp = NULL;
     temp = head -> nextptr;
     if(head -> nextptr == NULL){
          cout << "stack is empty" << endl;
     }
     else{
         head -> nextptr = head -> nextptr -> nextptr;
         free(temp);
     }
}
