#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    char color;
};

struct Node *newNode(int value)
{
    struct Node *newnode;
    newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->key = value;
    newnode->color = 'R';
    return newnode;
}


struct Node *find(struct Node *root, int value)
{   
    struct Node * parent=root;
    while (root != NULL && root->key != value){
    if (root->key < value){
        parent = root;
        root = root->right;}

    else if (root->key > value){
        parent = root;
        root = root->left;}
    }
    // 없을 때
    if (root == NULL)
        return parent;
    // 있을 때
    else
        return NULL; 
}


struct Node * insert(struct Node *root, int value)
{
    if (root == NULL){
        root = newNode(value);
        root -> color = 'B';
        return root;
    }

    if (find(root,value) == NULL){
        printf("Node%d is already exist\n", value);
    }
    else{
        struct Node *parentNode;
        parentNode = find(root,value);
        if (parentNode->key < value){
            parentNode->right = newNode(value);
            parentNode->right->parent = parentNode;
            insert_case1(parentNode->right);
        }
        else{
            parentNode->left = newNode(value);
            parentNode->left->parent = parentNode;
            insert_case1(parentNode->left);
        }
    }

}

void printTree(struct Node *root)
{
    if (root == NULL){
        return;
    }
    printTree(root->left);
    printf("%d ",root->key);
    printf("%c ", root->color);
    printTree(root->right);
}


struct Node *grandparent (struct Node * n)
{
    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;
}

struct Node *uncle(struct Node *n)
{
    struct Node *g = grandparent(n);
    if (g == NULL)
        return NULL;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}


// 부모가 없을 때 - root 노드 일때
void insert_case1(struct Node *n)
{
    if (n->parent == NULL)
        n->color = 'B'; 
    else{
        insert_case2(n);
    }
}
// 부모가 있을 때(검정)
void insert_case2(struct Node *n)
{
    if (n->parent->color == 'B')
        return;
    else
        insert_case3(n);
}

// 부모가 있을 때(빨강)
// uncle이 있을 때(빨강)
void insert_case3(struct Node *n)
{
    struct Node *u = uncle(n);
    struct Node *g = grandparent(n);
    if ((u != NULL) && (u->color == 'R')){
        n->parent->color = 'B';
        u->color = 'B';
        g->color = 'R';
        insert_case1(g);
    } else {
        insert_case4(n);
    }
}

void rotate_left(struct Node *n)
{
    struct Node *c = n->right;
    struct Node *p = n->parent;

    if (c->left != NULL)
        c->left->parent = n;
    n->right = c->left;
    n->parent = c;
    c->left = n;
    c->parent = p;

    if (p != NULL){
        if (p->left == n)
            p->left = c;
        else
            p->right = c;
    }
}

void rotate_right(struct Node *n)
{
    struct Node *c = n->left;
    struct Node *p = n->parent;

    if (c->right != NULL)
        c->right->parent = n;
    
    n->left = c->right;
    n->parent = c;
    c->right = n;
    c->parent = p;

    if(p != NULL){
        if(p->right == n)
            p->right = c;
        else
            p->left = c;
    }
}



// 부모가 있을 때(빨강)
// uncle이 있을 때(검정), 또는 uncle이 없을 때
// n이 안쪽에 있을 때
void insert_case4(struct Node * n)
{
    struct Node *g = grandparent(n);
    if (g != NULL)
    {
    if ((n == n->parent->right) && (n->parent == g->left)){
        rotate_left(n->parent);
        n = n-> left;
    } else if ((n == n->parent->left) && (n->parent == g->right)){
        rotate_right(n->parent);
        n = n-> right;
    }
    insert_case5(n);
    }
}

// 부모가 있을 때(빨강)
// uncle이 있을 때(검정)
// n이 바깥에 있을 때
void insert_case5(struct Node *n)
{
    struct Node *g = grandparent(n);

    n->parent->color = 'B';
    g->color = 'R';
    if (n == n->parent->left)
        rotate_right(g);
    else
        rotate_left(g);
}


// void main()
// {
//     struct Node * root = NULL;
//     root = insert(root, 50);
//     insert(root, 60);
//     insert(root, 70);
//     // insert(root, 80);
//     // insert(root,40);
//     // insert(root,45);
//     // insert(root,10);
//     printTree(root);
// }
