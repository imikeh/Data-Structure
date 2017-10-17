#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>

using namespace std;

/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Oct.25,2013*/
/*目的: 撰寫一個程式來記錄一個n*n的西洋棋中棋子所經過路徑的順序*/


int knight(class stack*,int); /*利用int型態fuction，若有解則回傳1，無解則回傳0*/
void push(class stack*,int,int,int); /*推入stack*/
void pop(class stack*); /*推出stack*/
void print(class stack*);

class stack
{
    public:
    int i,j,k;
    class stack *nextptr; /*stack下一個的指標*/
};

int main(void)
{
      class stack S;
      S.nextptr=NULL;
      int n;
      for(n=1;n<=6;n++){ /*題目要求n=1到n=6*/
            if(n==1){
                cout << " n = " << n << endl;
                cout<< " 1 " << endl;
                }
                else{
                        cout << " n = " << n << endl;
                        if(knight(&S,n)==0){ /*若回傳值為0則沒有答案*/
                                cout <<" No solution "<< endl;
                        }
                        else{ /*若回傳值為1則有答案*/
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
     int c=0,step=1,x=1,i,j,a,b; /*i,j代表陣列裡的列與行, step表示走的順序*/
     int array[n+1][n+1];
     int k[10][2]={{0,0},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{0,0}}; /*宣告k為方位 0和9是{0,0}*/

     for(i=1;i<=n;i++){ /*利用兩層迴圈讓全部元素歸0 */
         for(j=1;j<=n;j++){
              array[i][j]=0;
         }
     }

     i = 1;
     j = 1;

     array[i][j]=step; /*step從1開始，然後存入{1,1}這個位址*/
     push(head,i,j,3);

     start:
     for(x=c;x<=9;x++)
     {
          i = i + k[x][0];
          j = j + k[x][1];
          if(x==9){ /*若到k9表示八個方位都無法前進，所以退回上一個結果*/
              array[head -> nextptr -> i][head -> nextptr -> j]=0; /*利用指標將不行的步驟歸0*/
              c = head -> nextptr -> k + 1; /*c為pop之前的方位再+1，因為要換下一個方位*/
              pop(head); /*將stack最上層取出*/
              step = step -1;
          if(i==1&&j==1){ /*若k=9，i與j分別回到初始位置代表無解則回傳0*/
              return 0;
          }
          i = head -> nextptr -> i; /*i與j為pop之後的stack的最上層*/
          j = head -> nextptr -> j;
          goto start; /*從新的方位c開始跑迴圈*/
          }
          else if(i<1 || i>n || j<1|| j>n || array[i][j]!=0){ /*若i與j超出陣列或是小於陣列則重跑迴圈，換一個方向*/
              i = i - k[x][0];
              j = j - k[x][1];
              continue;
          }
          else{ /*代表有路可走，所以step+1並且push接下來i,j的位置與方位*/
              step = step +1;
              push(head,i,j,x);
              array[i][j] = step;
              c = 0;
              x = 0; /*將x,c歸0，從方向k0開始繼續跑迴圈*/
          }
          if(step==n*n){ /*若可到達n*n代表可以走到最後一步，所以有解回傳1，並印出陣列*/
              for(a=1;a<=n;a++){
                    for(b=1;b<=n;b++){
                        cout << setw(4) << right << array[a][b]; /*印出陣列*/
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
