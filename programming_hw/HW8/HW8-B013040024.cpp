#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define datanum 500000

#define SWAP(x,y) {long long int t; t = x; x = y; y = t;}

typedef struct calculation{
    int data;
    struct calculation* next;
}link;
link *hash_table[10];

int data[datanum]= {};

FILE *out_A,*out_B,*out_C,*in;

void poke(int* number, int L, int H){
    in = fopen("input.txt","w");
    srand(time(NULL));
    int n1=0, n2=0, temp=0;
    for(int i=0; i<H-L+1; i++){
        number[i]=i;
    }
    for(int i=0; i<H-L+1; i++){
        n1=rand()%(H-L+1);
        n2=rand()%(H-L+1);
        temp=number[n1];
        number[n1]=number[n2];
        number[n2]=temp;
    }
    for(int i=0; i<H-L+1; i++){
        number[i]+=L;
    }
    fprintf(in,"%d\n",datanum);
    for(int i=0; i<H-L+1; i++){
        fprintf(in,"%d\n",number[i]);
    }
    fclose(in);
}
void showHash(){
    link *p;
    for(int i=0;i<10;i++){
        for(p=hash_table[i]->next;p!=NULL;p=p->next){
            fprintf(out_C,"%d\n",p->data);
        }
    }
}
void addcalrsort(int x[],int n){
    out_C = fopen("outputC.txt","w");
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
        index = (x[i]*10)/datanum;

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
    fprintf(out_C,"Address Calculation sort need %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    showHash();
    fclose(out_C);
}

void bubble_sort(int a[], int n)
{
  int i, j, temp;
  out_A=fopen("outputA.txt","w");
  clock_t t1, t2;
  t1 = clock();

  for (i = 0 ; i < ( n - 1 ); i++)
  {
    for (j = 0 ; j < n - i - 1; j++)
    {
      if (a[j] > a[j+1])
      {
        temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }
  t2=clock();
  printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
  fprintf(out_A,"Bubble Sort need %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
  for ( i = 0 ; i < n ; i++ )
           fprintf(out_A,"%d\n", a[i]);

  fclose(out_A);
}

void quick_sort(int x[], int n){
    out_B = fopen("outputB.txt","w");
    clock_t t1, t2;
    t1 = clock();
    for (int i=0; i<n; ++i)
    {
        while (x[i] > 0)
        {
            int pivot = x[i], k = i;
            for (int j=i+1; x[j] < 0; ++j)
                if (x[j] < pivot)
                    swap(x[++k], x[j]);
            swap(x[i], x[k]);
            x[k] = -x[k];
        }
        x[i] = -x[i];
    }
    t2 = clock();
    printf("%.3f\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    fprintf(out_B,"quick sort need %.3f secs\n",((float)(t2-t1))/CLOCKS_PER_SEC);
    for(int i = 0; i <n; i++) { fprintf(out_B,"%d\n", x[i]); }
    fclose(out_B);
}

int main(){
    poke(data,0,datanum-1);
    in = fopen("input.txt","r");
    int num1;

    fscanf(in,"%d",&num1);

    int x[num1];
    for(int i=0;i<num1;i++){
        fscanf(in,"%d",&x[i]); /*讀取隨機變數存進陣列*/
    }
    printf("outputA\n");
    bubble_sort(x,num1);
    printf("outputB\n");
    quick_sort(x,num1);
    printf("outputC\n");
    addcalrsort(x,num1);

    fclose(in);

    return 0;
}
