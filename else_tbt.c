
/* C Program to Implement operations in Threaded Binary Search Tree */

#include <stdio.h>
#include <stdlib.h>

typedef enum {false,true} boolean;

struct node *in_succ(struct node *p);
struct node *in_pred(struct node *p);
struct node *insert(struct node *root, int ikey);
struct node *del(struct node *root, int dkey);
struct node *case_a(struct node *root, struct node *par,struct node *ptr);
struct node *case_b(struct node *root,struct node *par,struct node *ptr);
struct node *case_c(struct node *root, struct node *par,struct node *ptr);

void inorder( struct node *root);
void preorder( struct node *root);

struct node
{
    struct node *left;
    boolean lthread;
    int info;
    boolean rthread;
    struct node *right;
};

int main( )
{
    int choice,num;
    struct node *root=NULL;

    while(1)
    {
        printf("\n\t----------------------------");
        printf("\n\t TBT Operations");
        printf("\n\t----------------------------\n");

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
        }/*End of switch */
    }/*End of while */

    return 0;

}/*End of main( )*/


struct node *insert(struct node *root, int ikey)
{
    struct node *tmp,*par,*ptr;
    int found=0;

    ptr = root;
    par = NULL;

    while( ptr != NULL )
    {
        if( ikey == ptr->info)
        {
            found =1;
            break;
        }
        par = ptr;
        if(ikey < ptr->info)
        {
            if(ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if(ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    if(found)
        printf("\n Duplicate key \n");
    else
    {
        tmp=(struct node *)malloc(sizeof(struct node));
        tmp->info=ikey;
        tmp->lthread = true;
        tmp->rthread = true;

        if(par == NULL)
        {
            root=tmp;
            tmp->left=NULL;
            tmp->right=NULL;
        }
        else if(ikey < par->info)
        {
            tmp->left=par->left;
            tmp->right=par;
            par->lthread=false;
            par->left=tmp;
        }
        else
        {
            tmp->left=par;
            tmp->right=par->right;
            par->rthread=false;
            par->right=tmp;
        }
    }
    return root;

}/*End of insert( )*/


struct node *del(struct node *root, int dkey)
{
    struct node *par,*ptr;
    int found = 0;

    ptr = root;
    par = NULL;

    while(ptr != NULL)
    {
        if( dkey == ptr->info)
        {
            found = 1;
            break;
        }
        par = ptr;
        if(dkey < ptr->info)
        {
            if(ptr->lthread == false)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if(ptr->rthread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    if(found==0)
        printf("\n Data key not present in tree");

    else if(ptr->lthread==false && ptr->rthread==false)     /*2 children */
        root = case_c(root,par,ptr);
    else if(ptr->lthread==false )                           /* only left child */
        root = case_b(root, par,ptr);
    else if(ptr->rthread==false)                            /* only right child */
        root = case_b(root, par,ptr);
    else                                                    /* no child */
        root = case_a(root,par,ptr);
    return root;

}/*End of del( )*/


struct node *case_a(struct node *root, struct node *par,struct node *ptr )
{
    if(par==NULL) /*root node to be deleted*/
        root=NULL;
    else if(ptr==par->left)
    {
        par->lthread=true;
        par->left=ptr->left;
    }
    else
    {
        par->rthread=true;
        par->right=ptr->right;
    }

    free(ptr);
    return root;

}/*End of case_a( )*/

struct node *case_b(struct node *root,struct node *par,struct node *ptr)
{
    struct node *child, *s, *p;
    /*Initialize child*/
    if(ptr->lthread==false)     /* node to be deleted has left child */
        child=ptr->left;
    else                        /* node to be deleted has right child */
        child=ptr->right;

    if(par==NULL )              /* node to be deleted is root node */
        root=child;
    else if( ptr==par->left)    /* node is left child of its parent */
        par->left=child;
    else                        /* node is right child of its parent */
        par->right=child;

    s=in_succ(ptr);
    p=in_pred(ptr);

    if(ptr->lthread==false)      /* if ptr has left subtree */
        p->right=s;
    else if(ptr->rthread==false) /* if ptr has right subtree */
        s->left=p;

    free(ptr);
    return root;
}/*End of case_b( )*/


struct node *case_c(struct node *root, struct node *par,struct node *ptr)
{
    struct node *succ = ptr->right, *parsucc = ptr;

    while(succ->left!=NULL)             /*Find inorder successor and its parent*/
    {
        parsucc = succ;
        succ = succ->left;
    }
    ptr->info = succ->info;

    if(succ->lthread==true && succ->rthread==true)
        root = case_a(root, parsucc,succ);
    else
        root = case_b(root, parsucc,succ);

    return root;

}/*End of case_c( )*/


struct node *in_succ(struct node *ptr)
{
    if(ptr->rthread==true)
        return ptr->right;
    else
    {
        ptr=ptr->right;
        while(ptr->lthread==false)
            ptr=ptr->left;
        return ptr;
    }
}/*End of in_succ( )*/


struct node *in_pred(struct node *ptr)
{
    if(ptr->lthread==true)
        return ptr->left;
    else
    {
        ptr=ptr->left;
        while(ptr->rthread==false)
            ptr=ptr->right;

        return ptr;
    }
}/*End of in_pred( )*/


void inorder( struct node *root)
{
    struct node *ptr;
    if(root == NULL )
    {
        printf("Tree is empty");
        return;
    }
    ptr=root;

    /*Find the leftmost node */

    while(ptr->lthread==false)
        ptr=ptr->left;

    while( ptr!=NULL )
    {
        printf("%d ",ptr->info);
        ptr=in_succ(ptr);
    }

}/*End of inorder( )*/


void preorder(struct node *root )
{
    struct node *ptr;
    if(root==NULL)
    {
        printf("Tree is empty");
        return;
    }
    ptr=root;

    while(ptr!=NULL)
    {
        printf("%d ",ptr->info);
        if(ptr->lthread==false)
            ptr=ptr->left;
        else if(ptr->rthread==false)
            ptr=ptr->right;
        else
        {
            while(ptr!=NULL && ptr->rthread==true)
                ptr=ptr->right;
            if(ptr!=NULL)
                ptr=ptr->right;
        }
    }

}/*End of preorder( )*/
