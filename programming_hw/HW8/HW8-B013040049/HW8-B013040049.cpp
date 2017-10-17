/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Dec.22,2013*/
/*目的: 測試三種排序(sorting)演算法的執行效率*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

#define num 100 /*自訂資料量*/

typedef struct calculation{
    int data;
    struct calculation* next;
}link;
link *hash_table[10];

int n[num]= {};

FILE *randomfile,*outfileA,*outfileB,*outfileC;

void pokeralgorithm(int* number,int low,int up); /*撲克牌演算法 產生亂數*/
void selectionsort(int x[],int n); /*Selection 排序*/
void heapsort(int x[],int); /*Heap 排序*/
void sift(int x[],int,int);
void BuildMaxHeap(int x[],int);
void addcalrsort(int x[],int n); /*Addres Caculation 排序*/
void showHash();

int main(){
    pokeralgorithm(n,0,num-1);
    randomfile = fopen("input.txt","r");

    if(!randomfile){
        printf("no input.txt\n"); /*如果沒有產生input的話*/
        exit(1);
    }

    int num1;

    fscanf(randomfile,"%d",&num1);

    int x[num1];
    for(int i=0;i<num1;i++){
        fscanf(randomfile,"%d",&x[i]); /*讀取隨機變數存進陣列*/
    }

    printf("outputA\n");
    selectionsort(x,num1);
    printf("outputB\n");
    heapsort(x,num1);
    printf("outputC\n");
    addcalrsort(x,num1);

    fclose(randomfile);

    return 0;
}

void pokeralgorithm(int* number, int low, int up){ /*產生low~up的亂數*/
    randomfile = fopen("input.txt","w");
    srand(time(NULL));
    int n1=0, n2=0, temp=0;
    for(int i=0; i<up-low+1; i++){ /*分配數字0~up-low*/
        number[i]=i;
    }
    for(int i=0; i<up-low+1; i++){ /*兩個兩個互換*/
        n1=rand()%(up-low+1);
        n2=rand()%(up-low+1);
        temp=number[n1];
        number[n1]=number[n2];
        number[n2]=temp;
    }
    for(int i=0; i<up-low+1; i++){
        number[i]+=low;
    }
    fprintf(randomfile,"%d\n",num);
    for(int i=0; i<up-low+1; i++){
        fprintf(randomfile,"%d\n",number[i]);
    }
    fclose(randomfile);
}

void selectionsort(int x[],int n){
    outfileA = fopen("outputA.txt","w");
    unsigned int t1, t2;
    t1 = clock();
    for(int i=0; i<n; ++i){
            int min_index = i;
        for(int j=i+1; j<n; ++j)
            if (x[j] < x[min_index])
                min_index = j;
        swap(x[i],x[min_index]);
    }
    t2 = clock();
    fprintf(outfileA,"Insertion sort took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    for(int i=0;i<n;i++){
        fprintf(outfileA,"%d\n",x[i]);
    }
    fclose(outfileA);
}

void heapsort(int x[],int n){
    int temp;
    outfileB = fopen("outputB.txt","w");
    unsigned int t1, t2;
    t1 = clock();
    for(int i=(n-2)/2;i>=0;i--)
        sift(x,i,n);

    for(int i=n-1;i>=1;i--){
        temp=x[i];
        x[i]=x[0];
        x[0]=temp;
        sift(x,0,i);
    }
    t2 = clock();
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    fprintf(outfileB,"Heap sort took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    for(int i=0;i<n;i++){
        fprintf(outfileB,"%d\n",x[i]);
    }
    fclose(outfileB);
}

void addcalrsort(int x[],int n){
    outfileC = fopen("outputC.txt","w");
    unsigned int t1, t2;
    t1 = clock();
    int index;
    link *m,*p,*s;
    for(int i=0;i<10;i++){
        hash_table[i] = new link;
        hash_table[i]-> data = i;
        hash_table[i]-> next = NULL;

    }
    for(int i=0; i<n; i++){
        m = new link;
        m->data = x[i];
        m->next = NULL;
        index = (x[i]*10)/num;

    if(hash_table[index]->next==NULL){
            hash_table[index]->next = m;
    }
    else
    {
            p=hash_table[index];
            s=p->next;

            while(s!=NULL && s->data < x[i]){
                p=s;
                s=s->next;
            }
            if(s==NULL)
                p->next=m;
            else{
                p->next=m;
                m->next=s;
            }
    }
    }
    t2 = clock();
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    fprintf(outfileC,"Address Calculation sort took %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    showHash();
    fclose(outfileC);
}

void showHash(){
    link *p;
    for(int i=0;i<10;i++){
        for(p=hash_table[i]->next;p!=NULL;p=p->next){
            fprintf(outfileC,"%d\n",p->data);
        }
    }
}

void BuildMaxHeap(int x[],int n){
    int i;
    for(i=n/2-1;i>=0;i--)
        sift(x,i,n);
}

void sift(int a[],int head,int n){
     int temp,j;
     while(head*2+1<n){
            j=2*head+1;
     if(head*2+1==n-1){
     if(a[head]>a[j])
        break;
     }
     else{
            if(a[j+1]>a[j])
            j++;
            if(a[head]>a[j])
            break;
     }
     temp=a[head];
     a[head]=a[j];
     a[j]=temp;
     head=j;
     }
}

