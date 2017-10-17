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

		int c,e,N,P,Q,j;						//c,e,N,P,Q���Ȧs�ȡAj��counter
		N=1;
		while(1)
		{
			nptr top1 = NULL;						//�ŧilist
			nptr top2 = NULL;
			nptr top3 = NULL;
			nptr top4 = NULL;

			printf("�h�������X��? ");
			scanf("%d",&P);						//�s������
			for(j=0;j<P;j++)
			{
				printf("�Y�� : ");
				scanf("%d",&c);					//�s���Y��
				printf("���� : ");
				scanf("%d",&e);					//�s������
				insert(&top1,c,e);				//�[�Jlist
			}
			printf("�h�������X��? ");
			scanf("%d",&Q);

			if(P==0 && Q==0)
                break;

			for(j=0;j<Q;j++)
			{
				printf("�Y�� : ");
				scanf("%d",&c);
				printf("���� : ");
				scanf("%d",&e);
				insert(&top2,c,e);
			}
			printf("---------------------------\nCase %d :\n\n",N);
			N++;
			add(&top1,&top2,&top3);				//�N�h�����ۥ[
			multiply(&top1,&top2,&top4);		//�N�h�����ۭ�
		}

     	return 0;
 	}

  	void insert(nptr *top,int c,int e)
  	{
		int temp;
		nptr newptr,prev,current;
		newptr=malloc(sizeof(n));				//���t�O����Ŷ�

		newptr->coefficient=c;					//�N��Ʀs�Jnewptr
		newptr->exponent=e;
		newptr->next=NULL;
		if(*top==NULL)							//����list���Ū����p
			(*top)=newptr;
		else
		{
			current=(*top);
			prev=NULL;
			if((current->exponent)<e)			//��������Ƥp��Ĥ@�������p
			{
				newptr->next=current;
				(*top)=newptr;
			}
			else
			{
				if(current->next==NULL&&(current->exponent)>e)			//����list�u����@node�����p
					current->next=newptr;
				else if((current->exponent)==e)
					current->coefficient+=c;
				else
				{
					prev=current;
					current=current->next;
					while(current!=NULL)
					{
						if((prev->exponent)>e&&(current->exponent)<e)	//�N����̰��C���ǱƦC
						{
							newptr->next=current;
							prev->next=newptr;
						}
						else if((prev->exponent)==e)					//����Ƭ۵��h�X��
							prev->coefficient+=c;
						prev=current;
						current=current->next;
						if(current==NULL&&(prev->exponent)>e)			//�������������p
							prev->next=newptr;
						else if(current==NULL&&(prev->exponent)==e)
							prev->coefficient+=c;
					}
				}
			}
		}
		del(&(*top));						//�N�Y�Ƭ�0�����R��
	}

 	void del(nptr *top)
 	{
		nptr current,prev,temp;

		current=(*top);
		if(current==NULL)					//����list���Ū����p
			return;
		else if((current->next)==NULL)		//����list�u����@node�����p
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
			if(current->coefficient==0)		//�ˬd�����Y�ƬO�_��0
			{
				temp=current;
				current=current->next;
				(*top)=current;
				free(temp);
			}
			while(current->next!=NULL)		//�ˬd��L���O�_��0
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
		if(top==NULL)				//�S��node�h��0
		{
			printf("0\t0\n");
			return;
		}
		while((top->next)!=NULL)	//�Nnode�̧�print�X
		{
			printf("%d\t%d\n",top->coefficient,top->exponent);
			top=top->next;
		}
		if(top!=NULL)				//�B�z�������p
			printf("%d\t%d\n",top->coefficient,top->exponent);
	}

	void add(nptr *top1,nptr *top2,nptr *top3)
	{
		nptr current1,current2;
		int temp,i=0;

		current1=(*top1);
		current2=(*top2);

		while(current1!=NULL)		//��list3=list1
		{
			insert(&(*top3),(current1->coefficient),(current1->exponent));
			current1=current1->next;
		}
		current1=(*top1);
		while(current2!=NULL)		//��list2�Plist1���C�@�Ӷ��@���
		{
			while(current1!=NULL)
			{
				if((current1->exponent)==(current2->exponent))	//�p�G����۵��h�Y�Ƭۥ[
				{
					i=1;
					insert(&(*top3),(current2->coefficient),(current2->exponent));
					break;
				}
				current1=current1->next;
			}
			if(i==0)				//�p�G�S���Ӧ���h���Jlist3
				insert(&(*top3),current2->coefficient,current2->exponent);
			i=0;
			current1=(*top1);		//����list1
			current2=current2->next;
		}
		printf("ADD : \n");
		print(*top3);				//�N���Gprint�X
		printf("\n");
	}

	void multiply(nptr *top1,nptr *top2,nptr *top3)
	{
		nptr current1,current2;

		current1=(*top1);
		current2=(*top2);
		while(current2!=NULL)		//��list2�Plist1���C�ӼƤ��
		{
			while(current1!=NULL)
			{
				insert(&(*top3),(current1->coefficient)*(current2->coefficient),(current1->exponent)+(current2->exponent));	//�ۭ�
				current1=current1->next;
			}
			current2=current2->next;
			current1=(*top1);		//����list1
		}
		printf("MULTIPLY : \n");
		print(*top3);				//�N���Gprint�X
		printf("END\n");
	}
