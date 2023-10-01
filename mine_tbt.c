#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    int left_thread;
    int data;
    int right_thread;
    struct node *right;
}node;

node * create_node(int num)
{
    node * np =(node *)malloc(sizeof(node));
    np->data = num;

    np->left_thread = 1;
    np->right_thread = 1;

    np->left = NULL;
    np->right = NULL;

    return np;
}

node *insert(node *root,int num)
{
    node *p = create_node(num);

    if(root == NULL)
    {
        return p;
    }
    node *ptr=root,*prev=NULL;
    do
    {
        prev = ptr;
        if(ptr->data == num)
        {
            printf("Item already present in Tree");
            return ptr;
        }
        else if(ptr->data > num && !ptr->left_thread)
            ptr=ptr->left;

        else if(ptr->data < num && !ptr->right_thread)
            ptr=ptr->right;
        else
            break;

    }while(ptr != NULL);

    if(prev->data < num)
    {
        p->right = prev->right;
        p->left = prev;
        prev->right_thread = 0;
        prev->right = p;
    }
    else
    {
        p->left = prev->left;
        p->right = prev;
        prev->left_thread = 0;
        prev->left = p;
    }
    return root;
}

node *left_most(node *p)
{
    if(p == NULL)
        return NULL;
    while(!p->left_thread)
        p = p->left;
    return p;
}

void inorder(node *root)
{
    if(root == NULL)
    {
        printf("\n Tree is Empty.");
        return;
    }

    node *temp = left_most(root);
    while(temp != NULL)
    {
        printf(" %d  ",temp->data);
        if(!temp->right_thread)
            temp = left_most(temp->right);
        else
            temp = temp->right;
    }
}

void preorder(node *root)
{
    if(root == NULL)
    {
        printf("Tree is Empty.");
        return;
    }
    node *temp = root;
    do
    {
        printf(" %d  ",temp->data);

        if(!temp->left_thread)
            temp = temp->left;

        else if(!temp->right_thread)
            temp = temp->right;

        else
        {
            while(temp != NULL && temp->right_thread)
                temp=temp->right;
            if(temp != NULL)
                temp=temp->right;
        }

    }while(temp != NULL);
}

node *in_succ(node *ptr)
{
    if(ptr->right_thread)
        return ptr->right;
    ptr=ptr->right;
    while(!ptr->left_thread)
        ptr=ptr->left;
    return ptr;
}

node *in_pred(struct node *ptr)
{
    if(ptr->left_thread)
        return ptr->left;
    ptr=ptr->left;
    while(!ptr->right_thread)
        ptr=ptr->right;
    return ptr;
}

node *zero_child(node *root,node* par, node *ptr)
{
    if(par == NULL)
        root = NULL;
    else if(par->left == ptr)
    {
        par->left_thread = 1;
        par->left = ptr->left;
    }
    else
    {
        par->right_thread = 1;
        par->right = ptr->right;
    }
    free(ptr);
    return root;
}

node *single_child(node *root, node *par, node *ptr)
{
    node *child = !ptr->left_thread?ptr->left:ptr->right;

    if(par == NULL)
        root = child;
    else if(par->left == ptr)
        par->left = child;
    else
        par->right = child;

    node * succ = in_succ(ptr),*pred = in_pred(ptr);
    if(!ptr->right_thread)
        succ->left = pred;
    else if(!ptr->left_thread)
        pred->right = succ;
    free(ptr);
    return root;
}

node *both_child(node *root, node *par, node *ptr)
{
    if(par == NULL)
    {
        root = NULL;
        return root;
    }
    node *succ = ptr->right;
    while(succ->left != NULL)
    {
        par = succ;
        succ = succ->left;
    }
    ptr->data = succ->data;
    ptr = succ;
    if(ptr->left_thread && ptr->right_thread)
        root = zero_child(root,par,ptr);
    else
        root = single_child(root,par,ptr);
    return root;
}

node *del(node *root, int num)
{
    struct node *par,*ptr;
    int found = 0;

    ptr = root;
    par = NULL;

    while(ptr != NULL)
    {
        if( num == ptr->data)
        {
            found = 1;
            break;
        }
        par = ptr;
        if(num < ptr->data)
        {
            if(ptr->left_thread == 0)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if(ptr->right_thread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    if(found==0)
        printf("\n Data key not present in tree");

    else if(ptr->left_thread==0 && ptr->right_thread==0)     /*2 children */
        root = both_child(root,par,ptr);
    else if(ptr->left_thread==0 )                           /* only left child */
        root = single_child(root, par,ptr);
    else if(ptr->right_thread==0)                            /* only right child */
        root = single_child(root, par,ptr);
    else                                                    /* no child */
        root = zero_child(root,par,ptr);
    return root;

}
/*
node *del(node *root, int num)
{
    if(root == NULL)
    {
        printf("Tree is Empty.");
        return root;
    }
    node *ptr = root, *par = NULL;
    int isfound = 0;

    do
    {
        par = ptr;
        if(num == ptr->data)
        {
            isfound = 1;
            break;
        }
        else if(num > ptr->data && !ptr->right_thread)
            ptr = ptr->right;
        else if(num < ptr->data && !ptr->left_thread)
            ptr = ptr->left;
        else
            break;
    }while(ptr != NULL);

    if(!isfound)
    {
        printf("%d Not Found...",num);
        return root;
    }

    if((!ptr->left_thread) && (!ptr->right_thread))
        printf("both child - left-%d  right-%d ",ptr->left->data,ptr->right->data);
        //root = both_child(root,par,ptr);
    else if(!ptr->left_thread)
        printf("left child - left-%d  right-%d ",ptr->left->data,ptr->right->data);
        //root = single_child(root,par,ptr);
    else if(!ptr->right_thread)
        printf("right child - left-%d  right-%d ",ptr->left->data,ptr->right->data);
        //root = single_child(root,par,ptr);
    else
        printf("zero child - left-%d  right-%d ",ptr->left->data,ptr->right->data);
        //root = zero_child(root,par,ptr);
    return root;

}


//else tbt Inorder code.

void inorder(node *root)
{
    node *ptr;
    if(root == NULL )
    {
        printf("\n Tree is empty \n");
        return;
    }
    ptr=root;

    while(!ptr->left_thread)
        ptr=ptr->left;

    while( ptr!=NULL )
    {
        printf(" %d  ",ptr->data);
        ptr=in_succ(ptr);
    }
}

void preorder(node *root)
{
    node *ptr;
    if(root==NULL)
    {
        printf("\n Tree is empty \n");
        return;
    }
    ptr=root;

    while(ptr!=NULL)
    {
        printf(" %d  ",ptr->data);
        if(!ptr->left_thread)
            ptr=ptr->left;
        else if(!ptr->right_thread)
            ptr=ptr->right;
        else
        {
            while(ptr!=NULL && ptr->right_thread)
                ptr=ptr->right;
            if(ptr!=NULL)
                ptr=ptr->right;
        }
    }
}
*/

int main( )
{
    int choice,num;
    struct node *root=NULL;

    while(1)
    {
        printf("\n ----------------------------");
        printf("\n\t TBT Operations");
        printf("\n ----------------------------\n");

        printf("1. Insert \n");
        printf("2. Delete \n");
        printf("3. In order Traversal \n");
        printf("4. Pre order Traversal \n");
        printf("5. Quit \n");

        printf("\n Enter your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("\n Enter the Number to be inserted : ");
                scanf("%d",&num);
                root = insert(root,num);
                break;

            case 2:
                printf("\nEnter the number to be Deleted : ");
                scanf("%d",&num);
                root = del(root,num);
                break;

            case 3:
                inorder(root);
                break;

            case 4:
                preorder(root);
                break;

            case 5:
                exit(1);

            default:
                printf("\n Wrong choice \n");
        }
    }

    return 0;
}
