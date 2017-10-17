#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef struct Hnode        //樹所需的node
{
    int index;
    int times;
    bool isleft;
    struct Hnode *leftchild,*rightchild;
} node;

FILE *file1,*file2,*tempfile,*file3,*hfile;         //輸入輸出檔
deque <node> mydq;
deque <node>::iterator it;
deque <char> buffer;
stack <node*> mystack;
node *root;
string Htable[256];
int table[256];
int data[256];
int remain;
int two_power[] = {128, 64, 32, 16, 8, 4, 2, 1};
long long int originalSize;
long long int compressSize;
char compress[1000];
char decompress[1000];
float rate;
void buildTable(char ch);
void sortTable();
void sortdq();
void showTable();
void showdq();
void showtree(node *tree);
node *makenode(int index,int times);
node *setleft(node *child, node *father);
node *setright(node *child, node *father);
void buildHuffmanTree();
void buildCode(node* tree,char index,string s);
void docompress();
void countSize();
int countVarSize(int var);
void makeheader();
int buildTree(char index);
void decode();
void deleteTree(node *tree);
//declaration end
int main()
{
    originalSize = 0;
    compressSize = 0;
    int judge;
    cout << "enter '1' for compress '2' for decompress:";
    cin >> judge;
    if(judge==1)
    {
        cout << "Enter a filename:";
        scanf("%s",compress);

        file1 = fopen(compress, "rb");
        if(!file1)
        {
            cout << "file error!!" << endl;
            return 1;
        }

        char ch;
        while(!feof(file1))
        {
            fread(&ch, sizeof(char), 1, file1);
            originalSize++;
            if(feof(file1))
                break;
            buildTable(ch);
        }

        sortTable();
        buildHuffmanTree();
        //showtree(root);



        tempfile = fopen("temp.txt","wb");
        file2 = fopen("out.txt","wb");
        hfile = fopen("HUFFMANTABLE.txt","w");
        fprintf(file2,"%s\n",compress);
        for(int i=0; i<256; i++)
        {
            if(table[i]!=0)
            {
                string s;
                buildCode(root,data[i],s);
            }
        }
        fprintf(file2,"\n\n");
        fclose(hfile);
        fclose(file1);
        docompress();
        fclose(file2);
        fclose(tempfile);
        countSize();
        makeheader();

        while(!mystack.empty())
        {
            delete mystack.top();
            mystack.pop();
        }
        cout << endl;


        remove("temp.txt");
        cout << "compress done!!" << endl;

    }
    else if(judge==2)
    {
        cout << "input a file to decompress:";
        scanf("%s",decompress);

        file1 = fopen(decompress, "rb");
        if(!file1)
        {
            cout << "file error!!" << endl;
            return 1;
        }

        int i = 0;
        while(1)
        {
            char ch;
            fscanf(file1,"%c",&ch);
            if(ch=='\n')
                break;
            compress[i] = ch;
            i++;

        }

        char index;

        root = NULL;

        while(1)
        {
            fscanf(file1,"%c",&index);
            if(buildTree(index)==0)
                break;

        }


        char junk;

        fscanf(file1,"%d",&remain);

        while(1)//read the rate
        {
            fscanf(file1,"%c",&junk);
            if(junk=='\n')
                break;
        }
        //showtree(root);
        string s = compress;
        s.insert(0,"new");
        file3 = fopen(s.c_str(),"wb");

        if(root!=NULL)
          decode();

        cout << "  decompress done!!" << endl;
        //remove(compress);
        fclose(file3);
        fclose(file1);

        return 0;
    }

}

void decode()
{

    buffer.clear();
    char ch;
    unsigned char a;
    int fuck;
    node *p = root;
    fscanf(file1,"%c",&ch);
    while(!feof(file1))
    {
        a = ch;
        fuck = 0;
        for( int i = 0; i < 8; ++i )
        {
            fuck *= 2;
            fuck += a % 2;
            a /= 2;
        }
        for( int i = 0; i < 8; ++i )
        {
            buffer.push_back( (fuck%2)+'0' );
            fuck /= 2;
        }

        //printf("*%d ", buffer.size());

        while( buffer.size()>8 )
        {
            if(p->leftchild==NULL && p->rightchild==NULL)
            {
                fprintf(file3,"%c",(char)p->index);
                p = root;
            }
            else if(buffer.front()=='0')
            {
                if(p->leftchild==NULL)
                {
                    cout << "ERROR!!" << endl;
                    exit(1);
                }
                p=p->leftchild;
                buffer.pop_front();
            }
            else if(buffer.front()=='1')
            {
                if(p->rightchild==NULL)
                {
                    cout << "ERROR!!" << endl;
                    exit(1);
                }
                p=p->rightchild;
                buffer.pop_front();
            }
        }
        fscanf(file1,"%c",&ch);
    }

    while(buffer.size()>remain)
    {
        if(p->leftchild==NULL && p->rightchild==NULL)
        {
            fprintf(file3,"%c",(char)p->index);
            p = root;
        }
        if(buffer.front()=='0')
        {
            if(p->leftchild==NULL)
            {
                cout << "ERROR!!" << endl;
                exit(1);
            }
            p=p->leftchild;
            buffer.pop_front();
        }
        else if(buffer.front()=='1')
        {
            if(p->rightchild==NULL)
            {
                cout << "ERROR!!" << endl;
                exit(1);
            }
            p=p->rightchild;
            buffer.pop_front();
        }
    }
    if(p->leftchild==NULL && p->rightchild==NULL)
    {
        fprintf(file3,"%c",(char)p->index);
        p = root;
    }
    fclose(file2);
}

int buildTree(char index)
{

    char ch;
    int i = 0;
    node *cur,*parent = root;
    while(1)
    {
        fscanf(file1,"%c",&ch);
        if(ch=='\n')
            return 0;
        if(root==NULL)
        {
            root = makenode(-1,0);
            root->leftchild = NULL;
            root->rightchild = NULL;
            parent = root;
            i++;
        }
        if(ch=='0')
        {
            if(parent->leftchild==NULL)
            {
                cur = makenode(-1,i);
                cur->leftchild = NULL;
                cur->rightchild = NULL;
                setleft(cur,parent);
            }
            parent=parent->leftchild;
        }
        else if(ch=='1')
        {
            if(parent->rightchild==NULL)
            {
                cur = makenode(-1,i);
                cur->leftchild = NULL;
                cur->rightchild = NULL;
                setright(cur,parent);
            }
            parent = parent->rightchild;
        }
        else if(ch==' ')
        {
            parent-> index = (unsigned char)index;
            return 1;
        }
        i++;
    }
}

void makeheader()
{
    tempfile = fopen("temp.txt","rb");
    file2 = fopen("out.txt","ab");

    char ch;
    fprintf(file2,"%dremains originalSize = %lld  compressSize = %lld  rate = %06.2f\n",remain,originalSize,compressSize,rate);
    fread(&ch, sizeof(char), 1, tempfile);
    while(!feof(tempfile))
    {
        fprintf(file2,"%c",ch);
        fread(&ch, sizeof(char), 1, tempfile);
    }


    fclose(file2);
    fclose(tempfile);
}

int countVarSize(int var)
{
    int temp = var;
    int counter = 0;
    while(temp!=0)
    {
        temp/=10;
        counter++;
    }
    return counter;
}

void countSize()
{

    tempfile = fopen("temp.txt","rb");
    file2 = fopen("out.txt","rb");
    char ch;

    while(!feof(tempfile))
    {
        fread(&ch, sizeof(char), 1, tempfile);
        compressSize++;
    }
    while(!feof(file2))
    {
        fread(&ch, sizeof(char), 1, file2);
        compressSize++;
    }
    string s = "originalsize = compressSize = rating = remain = ";

    compressSize += countVarSize(originalSize);
    compressSize += s.length();
    compressSize += (1+6); //endl+rate;
    compressSize += countVarSize(compressSize);
    compressSize += countVarSize(remain);
    if(originalSize==0)
        rate = 0;
    else
        rate = compressSize/(double)originalSize;




    fclose(file2);
    fclose(tempfile);
}

void docompress()
{
    file1 = fopen(compress, "rb");

    char ch;
    unsigned char code;
    string s,sbuffer;
    unsigned char tochange[9];
    s.clear();
    sbuffer.clear();


    fscanf(file1,"%c",&ch);
    while(!feof(file1))
    {


        s += Htable[(unsigned char)ch];

        if(s.length()>=8)
        {
            for(int i=0; i<8; i++)
            {
                tochange[i] = s[i];
            }

            for(int i=8; i<s.length(); i++)
            {
                sbuffer += s[i];
            }

            s.clear();
            s+=sbuffer;

            sbuffer.clear();
            code = 0;
            for(int i=0; i<8; i++)
            {
                code+=two_power[i]*(tochange[i]-'0');
            }
            fprintf(tempfile,"%c",code);

        }
        fscanf(file1,"%c",&ch);
    }
    remain = 0;
    if(s.length()!=0)
    {

        for(int i=s.length(); i<8; i++)
        {
            s += '0';
            ++remain;
        }
        code = 0;
        for(int i=0; i<8; i++)
        {
            code += two_power[i]*(s[i]-'0');
        }
        fprintf(tempfile,"%c",code);
    }

}

void buildTable(char ch)    //建立ascii表
{
    int index = (unsigned char)ch;
    table[index]++;
}

void sortTable()            //排序ascii表
{
    for(int i=0; i<256; i++)
        data[i] = i;

    //bubbleSort
    //bubbleSort 做完會喪失index data記住index
    for(int i=0; i<256; i++)
    {
        for(int j=i+1; j<256; j++)
        {
            if(table[j] < table[j-1])
            {
                int temp = table[j];
                table[j] = table[j-1];
                table[j-1] = temp;

                int dtemp = data[j];
                data[j] = data[j-1];
                data[j-1] = dtemp;
            }


        }
    }
    //bubblesort End
}

void sortdq()               //排序deque
{
    deque <node>::iterator it2;

    for(it=mydq.begin(); it!=mydq.end(); it++)
    {
        for(it2 = (it+1); it2!=mydq.end(); it2++)
        {
            if(it2 -> times < (it2-1)->times)
            {
                node *temp = new(node);

                *temp = *it2;
                *it2 = *(it2-1);
                *(it2-1) = *temp;
                delete(temp);
            }
            else if(it2 -> times == (it2-1)->times)
            {
                if(it2 -> index < (it2-1)-> index)
                {
                    node *temp = new(node);
                    *temp = *it2;
                    *it2 = *(it2-1);
                    *(it2-1) = *temp;
                    delete(temp);
                }
            }

        }

    }
}

node *setleft(node *child, node *father) //建立左子樹
{
    child->isleft = true;
    father->leftchild = child;
    return father;
}

node *setright(node *child, node *father) //建立右子樹
{
    child->isleft = false;
    father->rightchild = child;
    return father;
}

node *makenode(int index,int times) //建立節點
{
    node *temp = new(node);
    temp -> index = index;
    temp -> times = times;
    return temp;
}

void buildHuffmanTree()             //建立壓縮霍夫曼樹
{
    for(int i=0; i<256; i++)
    {
        if(table[i]!=0)
        {
            node *temp = makenode(data[i],table[i]);
            temp->leftchild = NULL;
            temp->rightchild = NULL;
            mydq.push_back(*temp);
            delete(temp);
        }
    }
    sortdq();


    if(mydq.size()==1)
    {
        node *p,*p1;
        p = makenode(-1,-1);
        p->leftchild = NULL;
        p->rightchild = NULL;
        p1 = makenode(mydq.front().index,mydq.front().times);
        p1->leftchild = mydq.front().leftchild;
        p1->rightchild = mydq.front().rightchild;
        p = setleft(p1,p);
        root = p;
        mystack.push(p);
        return;
    }

    //push data End
    while(!mydq.empty())
    {
        node *p,*p1,*p2;
        p1 = makenode(mydq.front().index,mydq.front().times);
        p1->leftchild = mydq.front().leftchild;
        p1->rightchild = mydq.front().rightchild;
        mydq.pop_front();

        p2 = makenode(mydq.front().index,mydq.front().times);
        p2->leftchild = mydq.front().leftchild;
        p2->rightchild = mydq.front().rightchild;
        mydq.pop_front();


        p = makenode(p1->index,(p1->times+p2->times));
        p = setleft(p1,p);
        p = setright(p2,p);


        mystack.push(p1);
        mystack.push(p2);
        if(mydq.empty())
        {
            root = p;
            mystack.push(p);
            break;
        }
        mydq.push_front(*p);

        delete(p);
        sortdq();
    }


}

void buildCode(node* tree,char index,string s) //建立編碼
{

    if(tree!=NULL)
    {
        if(tree!=root)
        {
            if(tree->isleft==true)
                s+='0';
            else
                s+='1';
        }

        if(tree->index==(unsigned char)index && tree->leftchild==NULL && tree->rightchild==NULL)
        {
            Htable[(unsigned char)index] = s;
            fprintf(file2,"%c%s ",index,s.c_str());
            fprintf(hfile,"%d %s\n",index,s.c_str());
            return;
        }
        else
        {
            buildCode(tree->leftchild,index,s);
            buildCode(tree->rightchild,index,s);
        }

    }


}

void showdq()               //顯示deque
{
    for(it=mydq.begin(); it!=mydq.end(); it++)
    {
        cout << char(it -> index) << " ";
        cout << it -> times << endl;
    }
}

void showtree(node *tree)  //顯示霍夫曼樹
{
    if(tree!=NULL)
    {
        if(tree->leftchild==NULL && tree->rightchild==NULL)
            cout << (int)tree->index << " " << tree->times << endl;
        showtree(tree->leftchild);
        showtree(tree->rightchild);

    }
}

void deleteTree(node *tree)
{
    if(tree!=NULL)
    {
        deleteTree(tree->leftchild);
        deleteTree(tree->rightchild);
        //cout << (int)tree->index << " " << tree->times << endl;
        delete(tree);
    }


}

void showTable()            //顯示ascii表
{
    for(int i=0; i<256; i++)
    {
        if(table[i]!=0)
        {
            if(data[i]<128)
            {
                cout << (char)data[i] << " ";
                cout << table[i] << endl;
            }
            else
            {
                cout << char(255-data[i]) << " ";
                cout << table[i] << endl;
            }

        }
    }
}
