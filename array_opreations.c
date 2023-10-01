#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int menu()
{
    int val;
    clrscr();
    printf("Array operations");
    printf("\n\n 1. Array Insertion");
    printf("\n 2. Item Search");
    printf("\n 3. Element Deletion ");
    printf("\n 4. Element insert at pos ");
    printf("\n 5. Display ");
    printf("\n 6. Reverse ");
    printf("\n 7. Sorting ");
    printf("\n Press 0 for exit");

    printf("\n\n Enter your choice:  ");
    scanf("%d",&val);
    return val;
}

int element_insert(int *a)
{
    int i,size;
    printf("Enter size of arr: ");
    scanf("%d",&size);
    if(size>20)
    {
        printf("Size should not be greater then 20");
    }
    else
    {
        for(i=0;i<size;i++)
        {
            printf("Enter item %d: ",i+1);
            scanf("%d",&a[i]);
        }
    }

    return size;
}

void search(int *a,int s)
{
    clrscr();
    int ser,i;
    if(s<1)
    {
        printf("Array is empty");
        return;
    }
    printf("enter item to search: ");
    scanf("%d",&ser);
    for(i=0;i<s;i++)
    {
        if(a[i]==ser)
        {
            printf("Element %d found at index %d",ser,i);
            return ;
        }
    }
    printf("Element not found\n");
}

void reverse_arr(int *a,int s)
{
    int i;
    if(s<=0)
    {
        printf("Array is Empty");
        return;
    }
    for(i=s-1;i>=0;i--)
    {
        if(i==0)
            printf("%d ",a[i]);
        else
            printf("%d ->",a[i]);
    }
}

void element_del(int *a,int *s)
{
    int i,j,num,flag=0;
    int size = *s;
    if(size<=0)
    {
        printf("Array is empty");
        return ;
    }
    printf("Enter a number to delete: ");
    scanf("%d",&num);
    for(i=0;i<size;i++)
    {
        if(a[i]==num)
        {
            flag=1;
            for(j=i;j<size-1;j++)
            {
                a[j]=a[j+1];
            }
            (*s)--;
        }
    }
    if(!flag)
    {
        printf("Number not found");
    }
    else
    {
        printf("Number %d is delete",num);
    }
}

void element_ins_pos(int *a,int *s)
{
    int size,num,in,i;
    printf("Enter index: ");
    scanf("%d",&in);
    printf("Enter Element: ");
    scanf("%d",&num);
    size = *s;
    if(size<=0)
    {
        printf("Array is empty");
        return;
    }
    if(in>size-1)
    {
        printf("Index should in between 0 to %d",size-1);
        return;
    }
    for(i=size;i>=in;i--)
    {
        a[i+1]=a[i];
    }
    a[in]=num;
    (*s)++;

}

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort_arr(int *a,int s)
{
    int i,j,min,temp;
    for(i=0;i<=s-1;i++)
    {
        min=i;
        for(j=i+1;j<s;j++)
        {
            if(a[j] < a[min])
            {
                min = j;
            }
        }
        //swap(*a[j],*a[min]);
        temp = a[j];
        a[j] = a[min];
        a[min] = temp;
    }
}

void arr_show(int *a,int s)
{
    int i;
    if(s<1)
    {
        printf("Array is empty");
        return;
    }
    for(i=0;i<s;i++)
        printf("%d ",a[i]);
    printf("\n");
}

int main()
{
    int arr[20],n=0;
    while(1)
    {
        switch(menu())
        {

        case 1:
            n=element_insert(arr);
            break;
        case 2:
            search(arr,n);
            break;
        case 3:
            element_del(arr,&n);
            break;
        case 4:
            element_ins_pos(arr,&n);
            break;
        case 5:
            clrscr();
            arr_show(arr,n);
            break;
        case 6:
            reverse_arr(arr,n);
            break;
        case 7:
            sort_arr(arr,n);
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid choice!! Try again");

        }
    getch();
    }
    return 0;
}
