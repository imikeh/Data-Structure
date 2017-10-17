/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Jau.2,2014*/
/*目的: 給予一串數字，找出所有出現次數為奇數之數字*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int m[100],n[100],k=0;

class tree{
public:
    int data;
    tree *left;
    tree *right;
};
	tree *root;

 	int searchtree(tree *tree, int key);
    void addToTree(tree **cur,int temp);
 	int del(tree **pre,tree **cur,int value);
    void inorder(struct tree *s);
	void deletetree(tree *ptr);

    int leaf(tree **cur);
  	int two(tree **cur);
 	void deleteleafnode(tree **pre,tree **cur);
 	void deleteone(tree **pre,tree **cur);
 	void deletetwo(tree **cur);

int main(){
    struct tree *pre,*cur;
    root=pre=cur=NULL;

    int temp[100]={0};
    int i,j;

    k=i=j=0;

    for(j=0;j<100;j++){
        m[j]=n[j]=0;
    }

    while(1){
    scanf("%d",&temp[i]);
    if(temp[i]==-1){
        break;
    }
    i++;
    }

    for(i=0;temp[i]!=-1;i++){
        k=0;
        for(j=0;j<100;j++){
                m[j]=n[j]=0;
        }

        pre=cur=root;

        if(searchtree(root,temp[i])==0){
            addToTree(&root,temp[i]);
        }
        else{
            del(&pre,&cur,temp[i]);
        }
        cout << "node: ";
        inorder(root);
        cout << endl;
        cout << "left: ";
        for(j=0;m[j]!=0;j++){
            cout << m[j] <<" ";
        }
        cout << endl;
        cout << "right: ";
        for(j=0;n[j]!=0;j++){
            cout << n[j] <<" ";
        }
        cout << endl;
    }
    cout << "ans: ";
    inorder(root);
    cout << endl;
    deletetree(root);

    return 0;
}

int searchtree(tree *tree, int key){
    while (tree) {
    	if(key == tree->data){
            return 1;
    	}
    	if(key < tree->data){
                tree = tree->left;
    	}
    	else{
        tree = tree->right;
        }
    }
  return 0;
}

void addToTree(tree **cur,int temp){
    if(*cur == NULL){
        *cur =new struct tree;
        (*cur) -> left = NULL ;
        (*cur) -> data = temp;
        (*cur) -> right = NULL ;
    }
    else{
            if(temp < (*cur) -> data){
            addToTree(&((*cur) -> left),temp);
            }
            else{
            addToTree(&((*cur) -> right),temp);
            }
    }
}

int del(tree **pre,tree **cur,int value){
    if((*cur)->data > value){
        *pre=*cur;
        *cur =(*cur)->left;
        return del(pre,cur, value);
    }
    else if((*cur)->data < value){
        *pre=*cur;
        *cur = (*cur)->right;
        return del(pre, cur, value);
    }
    else{
    if(leaf(cur)){
        deleteleafnode(pre,cur);
    }
    else if(two(cur)){
        deletetwo(cur);
    }
    else{
        deleteone(pre, cur);
    }
    return value;
    }
}

void inorder(struct tree *s){
    if(s!= NULL ){
        inorder(s -> left);
        cout << s -> data << " ";
        if(s->left==NULL){
                 m[k]=-1;
        }
        else{
                 m[k]=s -> left -> data;
        }
        if(s->right==NULL){
                 n[k]=-1;
        }
        else {
                 n[k]=s -> right -> data;
        }
        k++;
        inorder(s -> right) ;
    }
}

void deletetree(tree *ptr){
    if(ptr!=NULL){
            deletetree(ptr->left);
            deletetree(ptr->right);
            delete(ptr);
    }
}

int leaf(tree **cur){
    if((*cur)->left==NULL && (*cur)->right==NULL){
            return 1;
    }
	return 0;
}

int two(tree **cur){
    if((*cur)->left && (*cur)->right){
            return 1;
    }
	return 0;
}

void deleteleafnode(tree **pre,tree **cur){
    if((*cur) == (*pre)->left){
        (*pre)->left =NULL;
    }
    else if((*cur) == (*pre)->right){
            (*pre)->right =NULL;
    }
    else if((*cur) == root){
        root=NULL;
    }
    delete(*cur);
}

void deleteone(tree **pre,tree **cur){
    struct tree *temp2;
    if((*cur)->left!=NULL){
            temp2 = (*cur)->left;
    }
    else{
            temp2 = (*cur)->right;
    }
    if((*cur)==(*pre)->left){
            (*pre)->left = temp2;
    }
    else if((*cur)==(*pre)->right){
            (*pre)->right = temp2;
    }
    else{
            root=temp2;
    }
    delete(*cur);
}

void deletetwo(tree **cur){
    struct tree *temp3,*temp4;
    temp3=(*cur)->right;

    if(temp3->left==NULL){
            (*cur)->data=temp3->data;
            (*cur)->right=temp3->right;
            temp4=temp3;
    }
    else{
        while(temp3->left->left!=NULL){
        temp3=temp3->left;
        temp4=temp3->left;
    }
    (*cur)->data=temp3->left->data;
    if(temp3->left->right!=NULL){
        temp3->left=temp3->left->right;
    }
    else{
        temp3->left=NULL;
    }
    }
    delete(temp4);
}
