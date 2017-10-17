#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 500000

typedef struct calnode
{
    int data;
    struct calnode* next;
} link;
link *hash_table[10];

typedef struct treenode
{
    struct treenode *leftnode;
    int data;
    struct treenode *rightnode;
} node;
int n[SIZE]= {};
FILE *randfile,*outfileA,*outfileB,*outfileC;

void poker(int* number,int small,int big); //撲克牌演算法 產生亂數
void binaryTreeSort(int x[],int n);        //二元樹排序法
void setTree(node **tree,int x);           //建立二元樹
void inorder(node *tree);
void insertsort(int x[],int n);            //插入排序法
void caladdrsort(int x[],int n);           //位置計算排序
void showHash();

int main()
{
    int i = 0;
    poker(n,0,SIZE-1);
    randfile = fopen("input.txt","r");

    if(!randfile)
    {
        cout << "NO input.txt!!" << endl;
        exit(1);
    }

    int num;
    fscanf(randfile,"%d",&num);
    int x[num];
    for(int i=0;i<num;i++)
        fscanf(randfile,"%d",&x[i]);

    insertsort(x,num);
    cout << "outputA done!" << endl;
    binaryTreeSort(x,num);
    cout << "outputB done!" << endl;
    caladdrsort(x,num);
    cout << "outputC done!" << endl;
    fclose(randfile);
    i++;

    return 0;
}

void poker(int* number, int small, int big) //產生 small~big 的亂數
{
    randfile = fopen("input.txt","w");
    srand(time(NULL));
    int n1=0, n2=0, temp=0;
    for(int i=0; i<big-small+1; i++) //數字分配 0~big-small
    {
        number[i]=i;
    }
    for(int i=0; i<big-small+1; i++) //兩兩交換
    {
        n1=rand()%(big-small+1);
        n2=rand()%(big-small+1);
        temp=number[n1];
        number[n1]=number[n2];
        number[n2]=temp;
    }
    for(int i=0; i<big-small+1; i++) //數字位移 small~big
    {
        number[i]+=small;
    }
    fprintf(randfile,"%d\n",SIZE);
    for(int i=0; i<big-small+1; i++) //數字列印
    {
        fprintf(randfile,"%d\n",number[i]);
    }
    fclose(randfile);
    cout << "random generated!" << endl;
}

void insertsort(int x[],int n)
{
    outfileA = fopen("outputA.txt","w");
    unsigned int t1, t2;
    int a[SIZE];

    t1 = clock();

    for(int i=0;i<n;i++)
    {
        a[i] = x[i];
    }
    int i,k,y;
    for(k=1; k<n; k++)
    {
        y = a[k];
        for(i=k-1; i>=0&&y<a[i]; i--)
            a[i+1] = a[i];
        a[i+1] = y;
    }
    t2 = clock();

    fprintf(outfileA,"partA insertion sort done, took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    for(int i=0;i<n;i++)
        fprintf(outfileA,"%d\n",a[i]);
    fclose(outfileA);

}

void binaryTreeSort(int x[],int n)
{
    outfileB = fopen("outputB.txt","w");
    unsigned int t1, t2;
    t1 = clock();
    node* root = NULL;
    for(int i=0; i<n; i++)
        setTree(&root,x[i]);
    t2 = clock();
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    fprintf(outfileB,"partB binaryTree sort done, took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    inorder(root);
    fclose(outfileB);
}

void setTree(node **tree,int x)
{
    if(*tree==NULL)
    {
        (*tree) = new node;
        (*tree)->leftnode = NULL;
        (*tree)->data = x;
        (*tree)->rightnode = NULL;
    }
    else
    {
        if(x>=(*tree)->data)
            setTree(&(*tree)->rightnode,x);
        else
            setTree(&(*tree)->leftnode,x);
    }

}

void inorder(node *tree)
{
    if(tree!=NULL)
    {
        inorder(tree->leftnode);
        fprintf(outfileB,"%d\n",tree->data);
        inorder(tree->rightnode);
    }

}

void caladdrsort(int x[],int n)
{
    outfileC = fopen("outputC.txt","w");
    unsigned int t1, t2;
    t1 = clock();
    int index;
    link *n1,*p,*s;
    for(int i=0;i<10;i++)
    {
        hash_table[i] = new link;
        hash_table[i]-> data = i;
        hash_table[i]-> next = NULL;

    }
    for(int i=0; i<n; i++)
    {
        n1 = new link;
        n1->data = x[i];
        n1->next = NULL;
        index = (x[i]*10)/SIZE;

        if(hash_table[index]->next==NULL)
        {
            hash_table[index]->next = n1;
        }

        else
        {
            p=hash_table[index];
            s=p->next;

            while(s!=NULL && s->data < x[i])
            {
                p=s;
                s=s->next;
            }
            if(s==NULL)
                p->next=n1;
            else
            {
                p->next=n1;
                n1->next=s;
            }
        }
    }
    t2 = clock();
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    fprintf(outfileB,"partB calculation address sort done, took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    showHash();
    fclose(outfileC);
}

void showHash()
{
    link *p;
    for(int i=0;i<10;i++)
    {
        for(p=hash_table[i]->next;p!=NULL;p=p->next)
        {
            fprintf(outfileC,"%d\n",p->data);
        }
    }
}









