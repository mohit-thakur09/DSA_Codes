#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    struct node *left;
    int data;
    int flag;
    struct node *right;
}node;

typedef struct stack
{
    struct node *arr[10];
    int tos;
}stack;

void push(stack *ps,node *ref)
{
    if(ps->tos == 9)
    {
        //printf("Stack Overflow");
        return;
    }
    ps->tos++;
    ps->arr[ps->tos]=ref;
}

node *pop(stack *ps)
{
    if(ps->tos == -1)
    {
        //printf("Stack Underflow");
        return NULL;
    }
    return ps->arr[ps->tos--];
}

void add_node(node **ref)
{
    int num;
    printf("Enter Number: ");
    scanf("%d",&num);

    node *p = (node *)malloc(sizeof(node));
    p->left = p->right = NULL;
    p->data = num;

    if(*ref == NULL)
    {
        *ref = p;
        printf("Node Append Successfully...");
        return;
    }

    node *prev,*temp = *ref;

    while(temp!=NULL)
    {
        prev=temp;
        if(temp->data > num)
            temp=temp->left;
        else
            temp=temp->right;
    }
    if(prev->data > num)
        prev->left = p;
    else
        prev->right = p;

    printf("Node Append Successfully...");
        return;

}

void pre_order(node *ref)
{
    stack s;
    s.tos = -1;

    if(ref == NULL)
    {
        printf("Tree Is Empty");
        return;
    }

    push(&s,ref);
    while(s.tos != -1)
    {
        ref = pop(&s);
        while(ref != NULL)
        {
            printf(" %d  ",ref->data);
            if(ref->right != NULL)
            {
                push(&s,ref->right);
            }
            ref = ref->left;
        }
    }
}

void in_order(node *ref)
{
    if(ref == NULL)
    {
        printf("\n Tree is Empty.");
        return;
    }
    stack s;
    s.tos = -1;

    while(ref != NULL || s.tos != -1)
    {
        while(ref != NULL)
        {
            push(&s,ref);
            ref= ref->left;
        }
        ref = pop(&s);
        printf("%d  ",ref->data);
        ref = ref->right;
    }
}

void post_order(node *ref)
{
    if(ref == NULL)
    {
        printf("\n Tree is Empty.");
        return;
    }
    stack s;
    s.tos = -1;

    while(ref != NULL || s.tos != -1)
    {
        while(ref != NULL)
        {
            push(&s,ref);
            ref->flag = 1;
            if(ref->right != NULL)
            {
                ref->right->flag = -1;
                push(&s,ref->right);
            }
            ref=ref->left;
        }
        ref=pop(&s);
        while(ref != NULL)
        {
            if(ref->flag == 1)
                printf("%d  ",ref->data);
            else
                break;
            ref=pop(&s);
        }
    }
}

int search_node(node *ref,int n,node **pc, node **pp)
{
    node *q=NULL;
    while(ref != NULL)
    {
        if(ref->data == n)
        {
            *pp = q;
            *pc = ref;
            return 1;
        }
        q=ref;

        if(ref->data > n)
            ref=ref->left;
        else
            ref=ref->right;
    }
    return 0;
}

void delete_node(node **ps)
{
    if(*ps == NULL)
    {
        printf("Tree is Empty.");
        return;
    }
    int x;
    printf("Enter Number to delete from tree.");
    scanf("%d",&x);

    node *succ, *child, *parent=NULL;
    int result = search_node(*ps,x,&child,&parent);

    if(result == 0)
    {
        printf("Node not found....");
        return;
    }

    if(child->right != NULL && child->left != NULL)
    {
        succ = child->right;
        parent = child;
        while(succ->left != NULL)
        {
            succ=succ->left;
            parent = succ;
        }
        child->data = succ->data;
        child=succ;
    }

    if(child->right == NULL && child->left == NULL)
    {
        if(parent == NULL)
            *ps = NULL;
        else if(parent->right == child)
            parent->right = NULL;
        else
            parent->left = NULL;
        free(child);
    }

    else if(child->right != NULL && child->left == NULL)
    {
        if(parent == NULL)
            *ps=NULL;
        else if(parent->right==child)
            parent->right = child->right;
        else
            parent->left = child->right;
        free(child);
    }
    else if(child->right == NULL && child->left != NULL)
    {
        if(parent == NULL)
            *ps=NULL;
        else if(parent->right==child)
            parent->right = child->left;
        else
            parent->left = child->left;
        free(child);
    }

}

int menu()
{
    int x;

    printf("\n-----------------------------------");
    printf("\n Binary Search Tree Operations");
    printf("\n-----------------------------------");

    printf("\n\n 1. Add Value");
    printf("\n 2. Pre Order ");
    printf("\n 3. In Order");
    printf("\n 4. Post Order");
    printf("\n 5. Delete");
    printf("\n 0. For Exit");

    printf("\n\n Enter Choice:  ");
    scanf("%d",&x);

    return x;
}

int main()
{
    int x;
    node *start=NULL;

    while(1)
    {
        switch(menu())
        {
        case 1:
            add_node(&start);
            break;
        case 2:
            pre_order(start);
            break;
        case 3:
            in_order(start);
            break;
        case 4:
            post_order(start);
            break;
        case 5:
            delete_node(&start);
            break;
        case 0:
            printf("\n Thank you... \n\t visit Again...");
            exit(0);
        default:
            printf("\n Invalid Choice... \n\t Try Again...");
        }
    }

    return 0;
}
