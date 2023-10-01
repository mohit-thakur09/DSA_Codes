#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
    int data;
    struct queue *next;
}dqueue;

dqueue *create_node(int n)
{
    dqueue *pn=(dqueue *)malloc(sizeof(dqueue));
    if(pn==NULL)
    {
        printf("\n Stack Overflow...");
        return NULL;
    }
    pn->data = n;
    pn->next = NULL;

    return pn;
}

void ins(dqueue **pr,dqueue **pf,int n)
{
    dqueue *p=create_node(n);
    if(*pr==NULL)
    {
        (*pr)=p;
        (*pf)=p;
        return;
    }
    (*pr)->next=p;
    (*pr)=p;
}

int del(dqueue **pr,dqueue **pf)
{
    if(*pf == NULL)
    {
        printf("\n Queue is Empty");
        return 0;
    }
    int x;
    if((*pr) == (*pf))
    {
        x=(*pr)->data;
        free(*pr);
        (*pr)=(*pf)=NULL;
        return x;
    }
    x=(*pf)->data;
    dqueue * temp = (*pf);
    (*pf)=temp->next;
    free(temp);
    return x;

}

int menu()
{
    int x;

    printf("\n-------------------------------------");
    printf("\n\t Dynamic Queue");
    printf("\n-------------------------------------");

    printf("\n 1. Insert ");
    printf("\n 2. Delete ");
    printf("\n 3. EXIT ");
    printf("\n Enter Number: ");
    scanf("%d",&x);

    return x;
}

int main()
{
    int item;
    dqueue *rear = NULL;
    dqueue *front = NULL;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n Enter Number: ");
            scanf("%d",&item);
            ins(&rear,&front,item);
            printf("\n Inserted Successfully...");
            break;
        case 2:
            item = del(&rear,&front);
            printf("\n Item Deleted %d",item);
            break;
        case 3:
            printf("\n Thank you ...!!");
            exit(0);
        default:
            printf("\n Wrong Choice... \n\t Try Again.");
        }
    }
    return 0;
}
