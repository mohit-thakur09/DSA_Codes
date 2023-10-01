#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int coeff;
    int expo;
    struct node *next;
}node;

node *create_node(int coeff,int expo)
{
    node *temp=(node *)malloc(sizeof(node));
    temp->coeff = coeff;
    temp->expo = expo;
    temp->next = NULL;
    return temp;
}

void append(node **eq, int coeff,int expo)
{
    node *p = create_node(coeff,expo);
    if(*eq == NULL)
    {
        *eq=p;
        printf("\n Node added successfully");
        return;
    }
    if((*eq)->expo >= p->expo)
    {
        p->next = (*eq);
        *eq = p;
        printf("\n Node added successfully");
        return;
    }
    node *temp = *eq,*prev = NULL;
    while(temp != NULL && temp->expo < p->expo)
    {
        prev=temp;
        temp=temp->next;
    }
    p->next = prev->next;
    prev->next=p;
    printf("\n Node added successfully");
    return;
}

void Addition(node *eq1,node *eq2, node** eq3)
{
    node *p, *p1 = eq1,*p2 = eq2,*q;

    while(p1!=NULL && p2!=NULL)
    {
        if(p1->expo == p2->expo)
        {
            p=create_node(p1->coeff+p2->coeff,p1->expo);
            p1=p1->next;
            p2=p2->next;
        }
        else if(p1->expo > p2->expo)
        {
            p=create_node(p2->coeff,p2->expo);
            p = p2;
            p2=p2->next;
        }
        else
        {
            p=create_node(p1->coeff,p1->expo);
            p = p1;
            p1=p1->next;
        }

        if(*eq3 == NULL)
            *eq3 = p;
        else
        {
            node *temp=*eq3;
            while(temp->next !=NULL)
                temp = temp->next;
            temp->next = p;
        }
    }
    q=p1!=NULL?p1:p2;
    node *temp=*eq3;
    while(temp->next !=NULL)
        temp = temp->next;
    temp->next = q;

}

void show(node *eq)
{
    if(eq==NULL)
    {
        printf("Equation is empty");
        return;
    }
    while(eq!=NULL)
    {
        if(eq->next == NULL)
            printf(" %d x%d",eq->coeff,eq->expo);
        else
            printf(" %d x%d  + ",eq->coeff,eq->expo);
        eq=eq->next;
    }
}

int menu()
{
    int x;
    printf("\n---------------------------------------");
    printf("\n\t Addition Of Polynomial");
    printf("\n---------------------------------------");

    printf("\n 1. Insert in Equation.");
    printf("\n 2. Addition.");
    printf("\n 3. substrate.");
    printf("\n 4. Show Equation 1, 2 or 3");
    printf("\n 5. Exit.");

    printf("\n\t Enter choice: ");
    scanf("%d",&x);
    return x;
}

int main()
{
    int inner_choice,coeff,expo;
    node *eq1 = NULL, *eq2 = NULL, *eq3 = NULL;

    while(1)
    {
        switch(menu())
        {
        case 1:
            printf("\n Equation number (1 or 2): ");
            scanf("%d",&inner_choice);
            if(inner_choice == 1)
            {
                printf("\n Enter coefficient for Eq1: ");
                scanf("%d",&coeff);
                printf("\n Enter Exponent for Eq1: ");
                scanf("%d",&expo);
                append(&eq1,coeff,expo);
            }
            else if(inner_choice == 2)
            {
                printf("\n Enter coefficient for Eq2: ");
                scanf("%d",&coeff);
                printf("\n Enter Exponent for Eq2: ");
                scanf("%d",&expo);
                append(&eq2,coeff,expo);
            }
            else
                printf("WRONG CHOICE");
            break;

        case 2:
            if(eq1 == NULL || eq2 == NULL)
                printf("\n Equation %s is Empty.",(eq1==NULL?"Eq1":"Eq2"));
            else
                Addition(eq1,eq2,&eq3);
            break;

        case 3:
            break;

        case 4:
            printf("Which equation : ");
            scanf("%d",&inner_choice);
            if(inner_choice == 1)
                show(eq1);
            else if(inner_choice==2)
                show(eq2);
            else if(inner_choice==3)
                show(eq3);
            else
                printf("WRONG CHOICE");
            break;

        case 5:
            exit(1);

        default:
            printf("\n Wrong choice... ");
        }
    }
}
