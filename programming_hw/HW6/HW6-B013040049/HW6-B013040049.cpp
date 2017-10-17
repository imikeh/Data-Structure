/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Nov.24,2013*/
/*目的: 設計一個程式，可以處理兩個多項式之加法與乘法*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node
{
    struct node *prev;
	struct node *next;
	int coefficient,exponent; /*coefficient係數,exponent次方*/
};

void input(node **list1,int x,int y);
void del(node **list1);

int main(){

    int p,q,x,y,c,d; /*p，q表示多項式有幾項，x為係數，y為次方，c為第幾個case*/

    struct node *head1,*head2; /*head1，head2*/

    struct node *head3,*head4; /*head3為加法，head4為減法*/

    struct node *add,*mul; /*加法，乘法*/

    c=1; /*先設定為one case*/

    head1=head2=head3=head4=NULL;

    while(1){

      scanf("%d",&p); /*幾項多像式*/
      d=p;

      while(p>0){
            scanf("%d %d",&x,&y);
            input(&head1,x,y);
            input(&head3,x,y);
            p=p-1;
      }

      scanf("%d",&q); /*幾項多像式*/

      if(d==0 && q==0){ /*若輸入p=0且q=0則程式結束*/
            break;
      }

      while(q>0){
            scanf("%d %d",&x,&y);
            input(&head2,x,y);
            q=q-1;
      }

      add=head2;

      while(add!=NULL){
            input(&head3,add -> coefficient,add -> exponent);
            add = add -> next;
      }

      mul=head1;

      while(mul!=NULL){
            add=head2;
         while(add!=NULL){
                input(&head4,add -> coefficient*mul -> coefficient,add -> exponent+mul -> exponent);
                add = add -> next;
         }
            mul=mul->next;
      }

      printf("\n");
      printf("CASE%d:\n",c); /*輸出*/
      printf("Addition\n");

      while(head3!=NULL){
            if(head3 -> coefficient != 0){
                printf("%d %d\n",head3->coefficient,head3->exponent);
                d=-1;
            }
            del(&head3);
       }

      if(d!=-1){
            printf("0 0\n");
      }

      d=0;

      printf("Multiply\n");

      while(head4!=NULL){
            if(head4 -> coefficient != 0){
                printf("%d %d\n",head4 -> coefficient,head4 -> exponent);
                d=-1;
            }
            del(&head4);
      }

      if(d!=-1){
            printf("0 0\n");
      }

      c++; /*counter計數*/

      while(head1!=NULL){
            del(&head1);
      }
      while(head2!=NULL){
          del(&head2);
      }

      printf("--------------End--------------\n");

   }
    return 0;
}

void input(node **list1,int x,int y){

		struct node *mike,*cur;
		mike = new node;
		mike -> coefficient=x; /*存係數*/
		mike -> exponent=y; /*存次方*/
		mike -> next = mike -> prev = NULL; /*讓next和prev皆為空的*/

		if((*list1)==NULL){
                (*list1) = mike;
        }
		else{
            if(mike -> exponent > (*list1) -> exponent){ /*比目前的次方還大*/
                  mike -> next = (*list1);
                  (*list1) -> prev = mike;
                  (*list1) = mike;
            }
            else {
                 cur = (*list1);
                 while(cur -> next != NULL && cur -> next -> exponent >= mike -> exponent){
                         cur = cur -> next;
                 }
                 if(cur -> exponent == mike -> exponent){ /*因為次方相等，所以係數相加*/
                      cur -> coefficient = cur -> coefficient + mike -> coefficient;
                      delete(mike);
                      return ;
                 }
                 if(cur -> next == NULL){ /*最小，排最後*/
                      cur -> next = mike;
                      mike -> prev = cur;
                 }
                 else{ /*排序在中間*/
                      cur -> next -> prev = mike;
                      mike -> next = cur -> next;
                      cur -> next = mike;
                      mike -> prev = cur;
                 }
            }
        }
	return ;
}

void del(node **list1){ /*刪除node*/
		struct node *mikemike;
		mikemike = (*list1);
		(*list1) = (*list1) -> next;
		if((*list1) != NULL){
                (*list1)->prev=NULL;
        }
		delete(mikemike);
	return ;
}



