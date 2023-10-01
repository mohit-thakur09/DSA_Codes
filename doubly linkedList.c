#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;

}node;

node *create_node(int x)
{
    node *p;
    p = (node *)malloc(sizeof(node));
    p->prev = NULL;
    p->data = x;
    p->next = NULL;
    return p;
}

void append(node **s,int x)
{
    node *p = create_node(x);
    if((*s)==NULL)
    {
        *s = p;
        return;
    }
    node *temp = *s;
    while(temp->next != NULL)
    {
        temp=temp->next;
    }
    temp->next=p;
    p->prev=temp;
}

void display(node *s)
{
    if(s==NULL)
    {
        printf("Doubly is Empty...");
        return;
    }
    while(s!=NULL)
    {
        printf("%d  ",s->data);
        s=s->next;
    }
}

int delete_node(node **s,int x)
{
    node *temp,*pv;
    if((*s)==NULL)
    {
        printf("Doubly linked list is Empty...");
        return 0;
    }
    if((*s)->data==x)
    {
        if((*s)->next==NULL)
        {
            free(*s);
            *s=NULL;
            return 1;
        }
        temp=(*s)->next;
        free(*s);
        temp->prev=NULL;
        *s=temp;
        return 1;
    }
    temp=*s;
    while(temp->data != x && temp->next != NULL)
    {
        pv=temp;
        temp=temp->next;
    }
    if(temp->data==x)
    {
        if(temp->next==NULL)
        {
            free(temp);
            pv->next=NULL;
            return 1;
        }
        pv->next=temp->next;
        temp->next->prev=pv;
        return 1;
    }
    return -1;
}

int menu()
{
    int choice = 0;

    printf("\n----------------------------------------------------");
    printf("\n\t Doubly Linked List Operations. \n");

    printf("\n 1. Append");
    printf("\n 2. Display");
    printf("\n 3. length");
    printf("\n 4. Search Item");
    printf("\n 5. Delete Item");
    printf("\n 6. Append in Sorted Manner");
    printf("\n 0. Exit");

    printf("\n----------------------------------------------------");
    printf("\n\t Enter your choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    node *start = NULL;
    int x,y;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n Enter Number: ");
            scanf("%d",&x);
            append(&start,x);
            break;
        case 2:
            display(start);
            break;
        case 3:
            //count(start);
            break;
        case 4:
        /*
            printf("\n Enter Number to search: ");
            scanf("%d",&x);
            y = search_node(start,x);
            if(y == -1)
                printf("\n Item Not Found...");
            else if(y == 0)
                 printf("\n Linked list Is Empty...");
            else
                printf("\n Item Found at Position is: %d",y);

        */
            break;
        case 5:
            printf("\n Enter Item : ");
            scanf("%d",&x);
            y=delete_node(&start,x);
            if(y == -1)
                printf("\n Item Not Found...");
            else if(y == 0)
                 printf("\n Linked list Is Empty...");
            else
                printf("\n Item %d Deleted...",y);
            break;
        case 6:
        /*
            printf("Enter Number : ");
            scanf("%d",&x);
            add_sort(&start,x);
         */
            break;
        case 0:
            exit(0);
        default:
            printf("\n You Entered WRONG the number...\n\t Try Again...");
        }
    }
    return 0;
}
