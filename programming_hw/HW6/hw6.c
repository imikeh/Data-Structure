# include <stdio.h>
# include <stdlib.h>

	struct node{
		int coefficient;
		int exponent;
		struct node *next;
	};

	typedef struct node n;
	typedef n *nptr;

	void insert(nptr *top,int c,int e);
	void del(nptr *top);
	void print(nptr top);
	void add(nptr *top1,nptr *top2,nptr *top3);
	void multiply(nptr *top1,nptr *top2,nptr *top3);

  	int main(){

		int c,e,N,P,Q,j;						//c,e,N,P,Q為暫存值，j為counter
		N=1;
		while(1)
		{
			nptr top1 = NULL;						//宣告list
			nptr top2 = NULL;
			nptr top3 = NULL;
			nptr top4 = NULL;

			printf("多項式有幾項? ");
			scanf("%d",&P);						//存取項數
			for(j=0;j<P;j++)
			{
				printf("係數 : ");
				scanf("%d",&c);					//存取係數
				printf("次方 : ");
				scanf("%d",&e);					//存取次方
				insert(&top1,c,e);				//加入list
			}
			printf("多項式有幾項? ");
			scanf("%d",&Q);

			if(P==0 && Q==0)
                break;

			for(j=0;j<Q;j++)
			{
				printf("係數 : ");
				scanf("%d",&c);
				printf("次方 : ");
				scanf("%d",&e);
				insert(&top2,c,e);
			}
			printf("---------------------------\nCase %d :\n\n",N);
			N++;
			add(&top1,&top2,&top3);				//將多項式相加
			multiply(&top1,&top2,&top4);		//將多項式相乘
		}

     	return 0;
 	}

  	void insert(nptr *top,int c,int e)
  	{
		int temp;
		nptr newptr,prev,current;
		newptr=malloc(sizeof(n));				//分配記憶體空間

		newptr->coefficient=c;					//將資料存入newptr
		newptr->exponent=e;
		newptr->next=NULL;
		if(*top==NULL)							//對應list為空的狀況
			(*top)=newptr;
		else
		{
			current=(*top);
			prev=NULL;
			if((current->exponent)<e)			//對應次方數小於第一項的狀況
			{
				newptr->next=current;
				(*top)=newptr;
			}
			else
			{
				if(current->next==NULL&&(current->exponent)>e)			//對應list只有單一node的狀況
					current->next=newptr;
				else if((current->exponent)==e)
					current->coefficient+=c;
				else
				{
					prev=current;
					current=current->next;
					while(current!=NULL)
					{
						if((prev->exponent)>e&&(current->exponent)<e)	//將次方依高低順序排列
						{
							newptr->next=current;
							prev->next=newptr;
						}
						else if((prev->exponent)==e)					//次方數相等則合併
							prev->coefficient+=c;
						prev=current;
						current=current->next;
						if(current==NULL&&(prev->exponent)>e)			//對應結尾的狀況
							prev->next=newptr;
						else if(current==NULL&&(prev->exponent)==e)
							prev->coefficient+=c;
					}
				}
			}
		}
		del(&(*top));						//將係數為0的項刪除
	}

 	void del(nptr *top)
 	{
		nptr current,prev,temp;

		current=(*top);
		if(current==NULL)					//對應list為空的狀況
			return;
		else if((current->next)==NULL)		//對應list只有單一node的狀況
		{
			if(current->coefficient==0)
			{
				temp=(*top);
				(*top)=NULL;
				free(temp);
			}
		}
		else
		{
			if(current->coefficient==0)		//檢查首項係數是否為0
			{
				temp=current;
				current=current->next;
				(*top)=current;
				free(temp);
			}
			while(current->next!=NULL)		//檢查其他項是否為0
			{
				prev=current;
				current=current->next;
				if(current->coefficient==0)
				{
					temp=current;
					prev->next=current->next;
					current=prev;
					free(temp);
				}
			}
		}
	}

  	void print(nptr top)
  	{
		if(top==NULL)				//沒有node則為0
		{
			printf("0\t0\n");
			return;
		}
		while((top->next)!=NULL)	//將node依序print出
		{
			printf("%d\t%d\n",top->coefficient,top->exponent);
			top=top->next;
		}
		if(top!=NULL)				//處理結尾狀況
			printf("%d\t%d\n",top->coefficient,top->exponent);
	}

	void add(nptr *top1,nptr *top2,nptr *top3)
	{
		nptr current1,current2;
		int temp,i=0;

		current1=(*top1);
		current2=(*top2);

		while(current1!=NULL)		//讓list3=list1
		{
			insert(&(*top3),(current1->coefficient),(current1->exponent));
			current1=current1->next;
		}
		current1=(*top1);
		while(current2!=NULL)		//讓list2與list1的每一個項作比對
		{
			while(current1!=NULL)
			{
				if((current1->exponent)==(current2->exponent))	//如果次方相等則係數相加
				{
					i=1;
					insert(&(*top3),(current2->coefficient),(current2->exponent));
					break;
				}
				current1=current1->next;
			}
			if(i==0)				//如果沒有該次方則插入list3
				insert(&(*top3),current2->coefficient,current2->exponent);
			i=0;
			current1=(*top1);		//重制list1
			current2=current2->next;
		}
		printf("ADD : \n");
		print(*top3);				//將結果print出
		printf("\n");
	}

	void multiply(nptr *top1,nptr *top2,nptr *top3)
	{
		nptr current1,current2;

		current1=(*top1);
		current2=(*top2);
		while(current2!=NULL)		//讓list2與list1的每個數比對
		{
			while(current1!=NULL)
			{
				insert(&(*top3),(current1->coefficient)*(current2->coefficient),(current1->exponent)+(current2->exponent));	//相乘
				current1=current1->next;
			}
			current2=current2->next;
			current1=(*top1);		//重制list1
		}
		printf("MULTIPLY : \n");
		print(*top3);				//將結果print出
		printf("END\n");
	}
