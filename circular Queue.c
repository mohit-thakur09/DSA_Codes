#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
    int arr[5];
    int rear,front;
}queue;

void insert(queue *q)
{
    int x;
    if( (q->rear+1 == q->front) || (q->rear == 4 && q->front == 0) )
    {
        printf("\n Queue Is Full...");
        return;
    }

    printf("\n Enter Number to Insert: ");
    scanf("%d",&x);

    (q->rear == 4)? (q->rear=0): (q->rear+=1);
    printf("Insert at : %d",q->rear);
    q->arr[q->rear] = x;

    if (q->front == -1)
        q->front =0;
}

void del(queue *q)
{
    if(q->front==-1)
    {
        printf("\n Queue is Empty...");
        return;
    }
    int x;
    x = q->arr[q->front];

    if(q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else if(q->front == 4)
        q->front = 0;
    else
        q->front += 1;

    printf("Deleted Number is: %d",x);
    printf("Deleted at : %d",q->front);

}

void display(queue q)
{
    if(q.rear == -1 && q.front==-1)
    {
        printf("Queue Is Empty.");
        return;
    }
    int i;
    for(i=q.front; i <= q.rear ;i++)
    {
        printf("%d  ",q.arr[i]);
    }
}

int menu()
{
    int choice = 0;

    printf("\n----------------------------------------------------");
    printf("\n\t Circular Queue Operations. \n");

    printf("\n 1. Insert");
    printf("\n 2. Delete");
    printf("\n 3. Traverse");
    printf("\n 4. Exit");

    printf("\n\t Enter your choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    queue q;
    q.rear = -1;
    q.front = -1;

    while(1)
    {
        switch(menu())
        {
        case 1:
            insert(&q);
            break;
        case 2:
            del(&q);
            break;
        case 3:
            display(q);
            break;
        case 4:
            exit(0);
        default:
            printf("\n You Entered WRONG number...\n\t Try Again...");
        }
    }
    return 0;
}
