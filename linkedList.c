#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef struct stack
{
    int arr[20];
    int tos;
}stack;


node * create_node(int x)
{
    node *p;
    p = (node *)malloc(sizeof(node));
    p->data = x;
    p->next = NULL;
    return p;
}

void append(node **s,int x)
{

    node *p = create_node(x),*temp;

    if(*s==NULL)
    {
        *s=p;
        printf("\n Element Append Successfully...");
        return;
    }
    temp = *s;
    while(temp->next != NULL)
    {
        temp=temp->next;
    }
    temp->next=p;
    printf("\n Element Append Successfully...");
}

void add_at_pos(node **s)
{
    int x,y;
    printf("Enter Position : ");
    scanf("%d",&x);

    printf("Enter Item : ");
    scanf("%d",&y);

    node *p = create_node(y);
    int len=0;

    node *demo=*s;
    while(demo != NULL)
    {
        demo=demo->next;
        len++;
    }

    if(*s==NULL && x==1)
    {
        *s=p;
        return;
    }
    if(len < x || len==0||x==0)
    {
        printf("\n Invalid Length...\n\t length of list is %d",len);
        return;
    }
    node *prev,*temp=*s;
    if(x==1)
    {
        p->next=temp;
        *s=p;
        return;
    }
    if(x==len)
    {
        while((x-1)!=0)
        {
            x--;
            temp=temp->next;
        }
        temp->next=p;
        return;
    }
    while((x-1)!=0)
    {
        x--;
        prev=temp;
        temp=temp->next;
    }
    p->next=temp;
    prev->next=p;
    return;
}

void add_sort(node **s,int x)
{
    node *prev,*temp=*s,*p = create_node(x);
    if(*s==NULL)
    {
        *s=p;
        return;
    }
    if(temp->data > x)
    {
        p->next=*s;
        *s=p;
        return;
    }
    while(temp->next!=NULL && temp->data < x)
    {
        prev = temp;
        temp=temp->next;
    }
    if(temp->data > x)
    {
        p->next=prev->next;
        prev->next=p;
        return;
    }
    temp->next=p;
}

int search_node(node *s,int x)
{
    if(s==NULL)
        return 0;
    int pos=0;
    while(s != NULL)
    {
        pos++;
        if(s->data == x)
            return pos;
        s = s->next;
    }
    return -1;
}

void pos_del(node **s)
{
    int pos,len=0,t=1;
    node *prev,*temp,*demo;

    if(*s==NULL)
    {
        printf("\n List is Empty...");
        return;
    }
    printf("\n Enter position to delete: ");
    scanf("%d",&pos);


    demo=*s;
    while(demo != NULL)
    {
        demo=demo->next;
        len++;
    }
    if(pos == 0 || pos > len)
    {
        printf("\n Invalid Position...\n list length is %d",len);
        return;
    }
    if(pos == 1)
    {
        (*s)=(*s)->next;
        free(s);
        return;
    }
    temp=*s;
    while(t!=pos)
    {
        prev=temp;
        temp=temp->next;
        t++;
    }
    prev->next=temp->next;
    free(temp);


}

int delete_node(node **s,int x)
{
    if(*s==NULL)
        return 0;
    node *temp=*s;
    if(temp->next==NULL && temp->data == x)
    {
        *s=temp->next;
        free(temp);
        return x;
    }
    node *prev;
    while(temp->next!=NULL)
    {
        if(temp->data == x && temp==*s)
        {
            *s=temp->next;
            free(temp);
            return x;
        }
        else if(temp->data == x )
        {
            prev->next = temp->next;
            free(temp);
            return x;
        }
        prev = temp;
        temp = temp->next;
    }
    if(temp->next == NULL && temp->data == x)
    {
        prev->next = temp->next;
        free(temp);
        return x;
    }
    else
        return -1;
}

void push(stack *s, int x)
{
    if(s->tos > 19)
    {
        printf("stack overflow...");
        return;
    }
    s->tos++;
    s->arr[s->tos]=x;

}

int pop(stack *s)
{
    int x;
    if(s->tos==-1)
    {
        printf("Stack is underflow");
        return;
    }
    x=s->arr[s->tos];
    s->tos--;
    return x;
}

void p_rev(node *p)
{
    stack s;
    s.tos=-1;

    if(p==NULL)
    {
        printf("linked list is Empty...");
        return;
    }
    while(p!=NULL)
    {
        push(&s,p->data);
        p=p->next;
    }
    while(s.tos>-1)
    {
        printf("%d ",pop(&s));
    }
}


void display(node *s)
{
    if(s == NULL)
    {
        printf("\n Linked List Is Empty...");
        return;
    }
    while(s != NULL)
    {
        printf("%d  ",s->data);
        s = s->next;
    }

}

void count(node **l)
{
    node *t=*l;
    int cot=0;
    if(t == NULL)
    {
        printf("\n Linked List Is Empty...");
        return;
    }
    while(t != NULL)
    {
        cot+=1;
        t=t->next;
    }
    printf("\n Total Number of Items in List Are: %d",cot);
}

void reverse(node **s)
{
    if(*s == NULL)
    {
        printf("\n List is Empty");
        return;
    }
    node *p=(*s),*q=NULL,*r=NULL;
    while(p != NULL)
    {
        q=p->next;
        p->next=r;
        r=p;
        p=q;
    }
    *s=r;
}

int menu()
{
    int choice = 0;

    printf("\n----------------------------------------------------");
    printf("\n\t Linked List Operations. \n");

    printf("\n 1. Append");
    printf("\n 2. Display");
    printf("\n 3. length");
    printf("\n 4. Search Item");
    printf("\n 5. Delete Item ~ value matches");
    printf("\n 6. Append in Sorted Manner");
    printf("\n 7. Print Reverse");
    printf("\n 8. Delete Item ~ given position");
    printf("\n 9. Add Node at position.");
    printf("\n 10. Reverse List");
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
            printf("\n Enter Value to Add in List: ");
            scanf("%d",&x);
            append(&start,x);
            break;
        case 2:
            display(start);
            break;
        case 3:
            count(&start);
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
        case 7:
            p_rev(start);
            break;
        case 8:
            pos_del(&start);
            break;
        case 9:
            add_at_pos(&start);
            break;
        case 10:
            reverse(&start);
            break;
        case 0:
            exit(0);
        default:
            printf("\n You Entered WRONG the number...\n\t Try Again...");
        }
    }
    return 0;
}
