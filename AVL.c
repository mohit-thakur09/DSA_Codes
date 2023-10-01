#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *left;
    int data;
    struct node *right;
    int height;
}*root=NULL;

struct stack
{
    struct node * arr[10];
    int tos;
};

int nodeHeight(struct node *ref)
{
    int hl = ref&&ref->left?ref->left->height:0;
    int hr = ref&&ref->right?ref->right->height:0;

    return hl>hr ? hl+1 : hr+1;
}


int balanceFactor(struct node *ref)
{
    int hl = ref&&ref->left?ref->left->height:0;
    int hr = ref&&ref->right?ref->right->height:0;

    return hl-hr;
}

struct node *LLRotation(struct node *ref)
{
    struct node *pl,*plr;

    pl = ref->left;
    plr= pl->right;

    pl->right = ref;
    ref->left = plr;

    ref->height = nodeHeight(ref);
    pl->height = nodeHeight(pl);

    if(ref == root)
        root=pl;
    return pl;
}

struct node * LRRotation(struct node *ref)
{
    struct node *pl,*plr;
    pl=ref->left;
    plr=pl->right;

    pl->right = plr->left;
    ref->left = plr->right;

    plr->right = ref;
    plr->left = pl;

    pl->height = nodeHeight(pl);
    ref->height = nodeHeight(ref);
    plr->height = nodeHeight(plr);

    if(root == ref)
        root=plr;
    return plr;
}

struct node *RRRotation(struct node *ref)
{
    struct node *pr,*prl;

    pr = ref->right;
    prl = pr->left;

    ref->right = prl;
    pr->left=ref;

    ref->height = nodeHeight(ref);
    pr->height = nodeHeight(pr);

    if(root==ref)
        root=pr;
    return pr;

}

struct node* RLRotation(struct node *ref)
{
    struct node *pr,*prl;
    pr = ref->right;
    prl = pr->left;

    pr->left = prl->right;
    ref->right = prl->left;

    prl->right = pr;
    prl->left = ref;

    pr->height = nodeHeight(pr);
    ref->height = nodeHeight(ref);
    prl->height = nodeHeight(prl);

    if(root == ref)
        root = prl;
    return prl;
}

struct node* append(struct node *ref,int x)
{
    if(ref == NULL)
    {
        struct node *p = (struct node *)malloc(sizeof(struct node));
        p->left = NULL;
        p->data = x;
        p->right = NULL;
        p->height = 1;

        return p;
    }

    if(x > ref->data)
        ref->right = append(ref->right,x);
    else
        ref->left = append(ref->left,x);

    ref->height = nodeHeight(ref);

    if(balanceFactor(ref) == 2 && balanceFactor(ref->left) == 1)
        return LLRotation(ref);

    if(balanceFactor(ref) == 2 && balanceFactor(ref->left) == -1)
        return LRRotation(ref);

    if(balanceFactor(ref) == -2 && balanceFactor(ref->right) == 1)
        return RLRotation(ref);

    if(balanceFactor(ref) == -2 && balanceFactor(ref->right) == -1)
        return RRRotation(ref);


    return ref;
}

void push(struct stack *s, struct node *n)
{
    if(s->tos==9)
    {
        printf("\n stack overflow");
        return ;
    }
    s->tos++;
    s->arr[s->tos]=n;
}

struct node * pop(struct stack *s)
{
    if(s->tos==-1)
    {
        printf("\n stack underflow");
        return NULL;
    }
    return s->arr[s->tos--];
}

void inorder(struct node *pr)
{
    struct stack s;
    s.tos=-1;

    if(pr==NULL)
    {
        printf("\n AVL is empty");
        return ;
    }
    while(pr||s.tos!=-1)
    {
        while(pr)
        {
            push(&s,pr);
            pr=pr->left;
        }
        pr=pop(&s);
        printf(" %d (%d)  ",pr->data,pr->height);
        pr=pr->right;
    }
}

struct node * delete_node(struct node *ref, int n)
{
    if(ref==NULL)
        return ref;
    if(ref->data > n)
        ref->left = delete_node(ref->left,n);
    else if(ref->data < n)
        ref->right = delete_node(ref->right,n);
    else
    {
        struct node *temp;
        if(ref->left == NULL || ref->right == NULL)
        {
            temp = ref->left?ref->left:ref->right;

            if(temp == NULL)
            {
                temp=ref;
                ref=NULL;
            }
            else
            {
                *ref=*temp;
            }
            free(temp);
        }
        else
        {
            temp=ref->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            ref->data = temp->data;
            ref->right = delete_node(ref->right,temp->data);
        }

    }

    if(ref == NULL)
        return ref;
    ref->height = nodeHeight(ref);

    if(balanceFactor(ref) == 2 && balanceFactor(ref->left) == 1)
        return LLRotation(ref);

    if(balanceFactor(ref) == 2 && balanceFactor(ref->left) == -1)
        return LRRotation(ref);

    if(balanceFactor(ref) == -2 && balanceFactor(ref->right) == 1)
        return RLRotation(ref);

    if(balanceFactor(ref) == -2 && balanceFactor(ref->right) == -1)
        return RRRotation(ref);

    return ref;
};

int menu()
{
    int choice;

    printf("\n--------------------------------");
    printf("\n\t AVL Tree");
    printf("\n--------------------------------");

    printf("\n\n 1. Add node.");
    printf("\n 2. Display.");
    printf("\n 3. Delete node.");
    printf("\n 0. Exit.");

    printf("\n Choose any Operation:  ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    int num;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n Enter Number to add: ");
            scanf("%d",&num);
            if(root==NULL)
                root=append(root,num);
            else
                append(root,num);
            printf("\n Node added Successfully...");
            break;
        case 2:
            inorder(root);
            break;
        case 3:
            printf("\n Enter Number to delete: ");
            scanf("%d",&num);
            root = delete_node(root,num);
            break;
        case 0:
            printf("\n Thank you....");
            exit(0);
        default:
            printf("\n Try Again, Wrong choice ...");
        }
    }
}
