/*作者姓名: B013040049 黃翊*/
/*撰寫日期: Jau.2,2014*/
/*目的: 給予一串數字，找出所有出現次數為奇數之數字*/

#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

class Btree{
public:
    int num;
    Btree* left;
    Btree* right;
    Btree* father;
    bool isleft;
    Btree(int n) : num(n), left(NULL), right(NULL), father(NULL), isleft(true){}
};

void deleteNode(Btree *node);
void deleteroot(Btree ** root);
void addToTree(int nums ,Btree** root);
void inorderleft(Btree *tree);
void inorderright(Btree *tree);
void inordernode(Btree *tree);
void cleanTree(Btree *tree);


int main(){

    int nums;
    Btree* root = NULL;

    while(1){
        cin >> nums;
        if(nums!=-1){
        addToTree(nums,&root);
        cout<<"node\t";
        inordernode(root);
        cout<<"\nleft\t";
        inorderleft(root);
        cout<<"\nright\t";
        inorderright(root);
        cout<<endl;
        }
        else if(nums==-1){
            break;
        }
    }
    cout << "Ans :   " ;
    inordernode(root);
    cleanTree(root);
    return 0;
}

void deleteNode(Btree *node){
    Btree *temp,*dtemp;
    if(node->left == NULL && node->right == NULL){
        if(node->isleft == true)
            node->father->left = NULL;
        else if(node->isleft == false)
            node->father->right = NULL;
        delete node;
    }
    else if(node->left != NULL && node->right == NULL){
        temp = node->left;
        temp->father = node->father;
        if(node->isleft == true){
            node->father->left = temp;
            temp->isleft = true;
        }
        else if(node->isleft == false){
            node->father->right = temp;
            temp->isleft = false;
        }
        delete node;
    }
    else if(node->left == NULL && node->right !=NULL){
        temp = node->right;
        temp->father = node->father;
        if(node->isleft == true)
            node->father->left = temp;
        else if(node->isleft == false)
            node->father->right = temp;
        delete node;
    }
    else if(node->left != NULL && node->right != NULL){
        temp=node->right;
        while(temp->left != NULL)
            temp = temp->left;
        node->num = temp->num;
        if(temp->right != NULL){
            dtemp = temp->right;
            dtemp->father = temp->father;
            if(temp != node->right){
                temp->father->left = dtemp;
                dtemp->isleft = true;
            }
            else
                node->right = dtemp;
        }
        else{
            if(temp != node->right)
                temp->father->left = NULL;
            else
                node->right = NULL;
        }
        delete temp;
    }
}

void deleteroot(Btree ** root){
    Btree *temp,*dtemp;
    if((*root)->left == NULL && (*root)->right == NULL)
        *root=NULL;
    else if((*root)->left != NULL && (*root)->right == NULL){
        temp = (*root)->left;
        temp->father = NULL;
        delete *root;
        temp->isleft = true;
        *root = temp;
    }
    else if((*root)->left == NULL && (*root)->right !=NULL){
        temp = (*root)->right;
        temp->father = NULL;
        delete *root;
        temp->isleft = true;
        *root = temp;
    }
    else if((*root)->left != NULL && (*root)->right != NULL){
        temp=(*root)->right;
        while(temp->left != NULL)
            temp = temp->left;
        (*root)->num = temp->num;
        if(temp->right != NULL){
            dtemp = temp->right;
            dtemp->father = temp->father;
            if(temp != (*root)->right){
                temp->father->left = dtemp;
                dtemp->isleft = true;
            }
            else
                (*root)->right = dtemp;
        }
        else{
            if(temp != (*root)->right)
                temp->father->left =NULL;
            else
                (*root)->right = NULL;
        }
        delete temp;
    }
}

void addToTree(int nums ,Btree** root){

    Btree *newnode,*current;
    int flag = 0;
    newnode = new Btree(nums);

    if(*root == NULL){
        *root = newnode;
    }
    else{
        current = *root;

        while( !flag ){
            if(nums < current->num){
                if(current->left == NULL){
                    current->left = newnode;
                    newnode->father = current;
                    newnode->isleft = true;
                    flag = 1;
                }
                else{
                    current = current->left;
                }
            }
            else if(nums > current->num){
                if(current->right == NULL){
                    current->right = newnode;
                    newnode->father = current;
                    newnode->isleft = false;
                    flag = 1;
                }
                else{
                    current = current->right;
                }
            }
            else{
                delete newnode;
                if(current == *root){
                    deleteroot(root);
                }
                else{
                    deleteNode(current);
                }
                flag = 1;
                delete current;
           }

        }

    }

}

void inordernode(Btree *tree){
    if(tree != NULL){
        inordernode(tree->left);
        cout<<tree->num<<"\t";
        inordernode(tree->right);
    }
}

void inorderleft(Btree *tree){
    if(tree != NULL){
        inorderleft(tree->left);
        if(tree->left == NULL)
            cout<<"-1\t";
        else
            cout<<tree->left->num<<"\t";
        inorderleft(tree->right);
    }
}

void inorderright(Btree *tree){
    if(tree != NULL){
        inorderright(tree->left);
        if(tree->right == NULL)
            cout<<"-1\t";
        else
            cout<<tree->right->num<<"\t";
        inorderright(tree->right);
    }
}

void cleanTree(Btree *tree){
    if(tree != NULL){
        cleanTree(tree->left);
        cleanTree(tree->right);
        delete tree;
    }
}
