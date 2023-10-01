#include<stdio.h>
#include<stdlib.h>

void insert_node(int arr[],int i, int n)
{
    while(i>1)
    {
        if(n < arr[i/2])
        {
            arr[i]=n;
            return;
        }
        arr[i]=arr[i/2];
        i=i/2;
    }
    arr[i]=n;
}

void del(int arr[], int index)
{
    if(index <= 1)
    {
        printf("\n Tree is Empty.");
        return;
    }
    int i=1,j=i*2;
    arr[1]=arr[index-1];
    index--;
    while(j < index)
    {
        if(arr[j+1] > arr[j])
        {
            j=j+1;
        }
        if(arr[j] > arr[i])
        {
            int temp;
            temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
            //swap(&arr[j],&arr[i]);
            i=j;
            j=i*2;
        }
        else
            break;
    }
}

void swap(int *p, int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}


void view(int arr[], int i)
{
    if(i <= 1)
    {
        printf("\n Tree is empty.");
        return ;
    }
    int j;
    for(j=1;j<i;j++)
        printf(" %d  ",arr[j]);
}

int menu()
{
    int ch;

    printf("\n------------------------------------------");
    printf("\n\t Heap Tree Operation");
    printf("\n------------------------------------------");

    printf("\n\n 1. Insert Element.");
    printf("\n 2. Display heap tree.");
    printf("\n 3. Delete Element.");
    printf("\n Press 0 for Exit.");

    printf("\n\n Enter your choice: ");
    scanf("%d",&ch);
    return ch;
}

int main()
{
    int x,arr[10];
    static int index = 1;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n Enter Number: ");
            scanf("%d",&x);
            insert_node(arr,index++,x);
            printf("\n Node added successfully.");
            break;
        case 2:
            view(arr,index);
            break;
        case 3:
            del(arr,index--);
            printf("\n Node deleted Successfully...");
            break;
        case 0:
            printf("\n Thank You for Using....\n\n");
            exit(0);
            break;
        default:
            printf("\n Wrong choice....");
        }
    }
}
