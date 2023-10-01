#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node *create_node(int x)
{
    node *p;
    p = (node *)malloc(sizeof(node));
    p->data = x;
    p->next = NULL;
    return p;
}

void append(node **s,int x)
{
    node *temp,*prev,*p=create_node(x);

    if(*s==NULL)
    {
        *s=p;
        p->next=p;
        return;
    }
    temp=*s;
    while(temp->next != (*s))
    {
        prev=temp;
        temp=temp->next;
    }
    temp->next=p;
    p->next=*s;
}

void add_sort(node **s,int x)
{
    node *p = create_node(x);

    if(*s == NULL)
    {
        *s=p;
        p->next=*s;
        return;
    }
    node *prev,*temp=*s;

    if(x < (*s)->data)
    {
        while(temp->next != *s)
        {
            temp=temp->next;
        }
        p->next=*s;
        *s=p;
        temp->next=p;
        return;
    }

    while(temp->data < x && temp->next != *s)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp->data > x)
    {
        p->next=temp;
        prev->next=p;
        return;
    }

    p->next=temp->next;
    temp->next=p;
}

void display(node *s)
{
    if(s==NULL)
    {
        printf("\n C Linked List is Empty...");
        return;
    }
    node *temp=s;
    do
    {
        printf("%d  ",temp->data);
        temp=temp->next;

    }while(temp != s);
}

int delete_node(node **s,int x)
{
    if((*s)==NULL)
    {
        printf("C Linked List is Empty...");
        return 0;
    }
    node *temp,*prev;
    if((*s)->data == x)
    {
        if((*s)==(*s)->next)
        {
            free(*s);
            *s=NULL;
            return x;
        }
        temp=*s;
        while(temp->next != (*s))
        {
            temp=temp->next;
        }
        *s=(*s)->next;
        free(temp->next);
        temp->next=*s;
        return x;
    }
    temp=*s;
    do
    {
        prev = temp;
        temp = temp->next;
    }while(temp != (*s) && temp->data != x);
    if(temp->data == x)
    {
        prev->next=temp->next;
        free(temp);
        return x;
    }
    return -1;
}

int search_node(node *s,int x)
{
    if(s==NULL)
    {
        return 0;
    }
    if(s->next==s)
    {
        if(s->data==x)
            return 1;
        return -1;
    }
    int pos=0;
    node *temp=s;
    do{
        pos++;
        if(temp->data == x)
            return pos;
        temp=temp->next;
    }
    while(temp !=s);
    return -1;
}

void count(node *s)
{
    if(s==NULL)
    {
        printf("Circular Linked List is Empty...");
        return;
    }
    node *temp=s;
    int total = 1;
    while(temp->next != s)
    {
        total++;
        temp=temp->next;
    }
    printf("Total Number of Items : %d",total);
}

int menu()
{
    int choice = 0;

    printf("\n----------------------------------------------------");
    printf("\n\t Circular Linked List Operations. \n");

    printf("\n 1. Append");
    printf("\n 2. Display");
    printf("\n 3. length");
    printf("\n 4. Search Item");
    printf("\n 5. Delete Item ~ value matches");
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
            count(start);
            break;
        case 4:
            printf("\n Enter Number to search: ");
            scanf("%d",&x);
            y = search_node(start,x);
            if(y == -1)
                printf("\n Item Not Found...");
            else if(y == 0)
                 printf("\n Linked list Is Empty...");
            else
                printf("\n Item Found at Position is: %d",y);
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
            printf("Enter Number : ");
            scanf("%d",&x);
            add_sort(&start,x);
            break;
        case 0:
            exit(0);
        default:
            printf("\n You Entered WRONG the number...\n\t Try Again...");
        }
    }
    return 0;
}
