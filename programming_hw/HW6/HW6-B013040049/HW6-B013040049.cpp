/*�@�̩m�W: B013040049 ����*/
/*���g���: Nov.24,2013*/
/*�ت�: �]�p�@�ӵ{���A�i�H�B�z��Ӧh�������[�k�P���k*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node
{
    struct node *prev;
	struct node *next;
	int coefficient,exponent; /*coefficient�Y��,exponent����*/
};

void input(node **list1,int x,int y);
void del(node **list1);

int main(){

    int p,q,x,y,c,d; /*p�Aq��ܦh�������X���Ax���Y�ơAy������Ac���ĴX��case*/

    struct node *head1,*head2; /*head1�Ahead2*/

    struct node *head3,*head4; /*head3���[�k�Ahead4����k*/

    struct node *add,*mul; /*�[�k�A���k*/

    c=1; /*���]�w��one case*/

    head1=head2=head3=head4=NULL;

    while(1){

      scanf("%d",&p); /*�X���h����*/
      d=p;

      while(p>0){
            scanf("%d %d",&x,&y);
            input(&head1,x,y);
            input(&head3,x,y);
            p=p-1;
      }

      scanf("%d",&q); /*�X���h����*/

      if(d==0 && q==0){ /*�Y��Jp=0�Bq=0�h�{������*/
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
      printf("CASE%d:\n",c); /*��X*/
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

      c++; /*counter�p��*/

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
		mike -> coefficient=x; /*�s�Y��*/
		mike -> exponent=y; /*�s����*/
		mike -> next = mike -> prev = NULL; /*��next�Mprev�Ҭ��Ū�*/

		if((*list1)==NULL){
                (*list1) = mike;
        }
		else{
            if(mike -> exponent > (*list1) -> exponent){ /*��ثe�������٤j*/
                  mike -> next = (*list1);
                  (*list1) -> prev = mike;
                  (*list1) = mike;
            }
            else {
                 cur = (*list1);
                 while(cur -> next != NULL && cur -> next -> exponent >= mike -> exponent){
                         cur = cur -> next;
                 }
                 if(cur -> exponent == mike -> exponent){ /*�]������۵��A�ҥH�Y�Ƭۥ[*/
                      cur -> coefficient = cur -> coefficient + mike -> coefficient;
                      delete(mike);
                      return ;
                 }
                 if(cur -> next == NULL){ /*�̤p�A�Ƴ̫�*/
                      cur -> next = mike;
                      mike -> prev = cur;
                 }
                 else{ /*�ƧǦb����*/
                      cur -> next -> prev = mike;
                      mike -> next = cur -> next;
                      cur -> next = mike;
                      mike -> prev = cur;
                 }
            }
        }
	return ;
}

void del(node **list1){ /*�R��node*/
		struct node *mikemike;
		mikemike = (*list1);
		(*list1) = (*list1) -> next;
		if((*list1) != NULL){
                (*list1)->prev=NULL;
        }
		delete(mikemike);
	return ;
}



