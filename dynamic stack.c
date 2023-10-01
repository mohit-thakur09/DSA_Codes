#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int data;
    struct stack *next;
}dstack;

dstack *create_node(int n)
{
    dstack *pn=(dstack *)malloc(sizeof(dstack));
    if(pn==NULL)
    {
        printf("\n Stack Overflow...");
        return NULL;
    }
    pn->data = n;
    pn->next = NULL;
    return pn;

}

void push(dstack **ptos, int num)
{
    dstack *p = create_node(num);
    if(*ptos == NULL)
    {
        *ptos=p;
        return;
    }
    p->next = (*ptos);
    *ptos = p;
}

int pop(dstack **ptos)
{
    int x;
    if(*ptos==NULL)
    {
        printf("\n Stack Underflow...");
        return 0;
    }
    dstack *temp;
    temp=*ptos;
    x=temp->data;
    *ptos=temp->next;
    free(temp);
    return x;
}

int menu()
{
    int x;

    printf("\n-------------------------------------");
    printf("\n\t Dynamic Stack");
    printf("\n-------------------------------------");

    printf("\n 1. PUSH ");
    printf("\n 2. POP ");
    printf("\n 3. EXIT ");
    printf("\n Enter Number: ");
    scanf("%d",&x);

    return x;
}

int main()
{
    int item;
    dstack *tos = NULL;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("Enter Number: ");
            scanf("%d",&item);
            push(&tos,item);
            printf("Inserted Successfully...");
            break;
        case 2:
            item = pop(&tos);
            printf("Item Deleted %d",item);
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
