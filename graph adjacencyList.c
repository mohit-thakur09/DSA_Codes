#include<stdio.h>
#include<stdlib.h>

struct edge{

    char data;
    struct edge *nedge;
};

struct vertex{

    char data;
    struct vertex *nvertex;
    struct edge *nedge;
};

struct vertex *findVertex(struct vertex *pv,char ch)
{
    if(pv == NULL)
    {
        printf("\n\t Graph is Empty.");
        return NULL;
    }
    while(pv->nvertex != NULL && pv->data != ch)
    {
        pv=pv->nvertex;
    }
    if(pv->data == ch)
        return pv;
    return NULL;
};

void findEdge(struct vertex *pv, char ch1,char ch2)
{
    if(pv == NULL)
    {
        printf("\n\tGraph is Empty.");
        return;
    }
    struct edge *temp;
    /*
    if(pv->data == ch1)
    {
        temp=pv->nedge;
        if(temp == NULL)
        {
            printf("first: Not Found!");
            return;
        }
        while(temp != NULL)
        {
            if(temp->data == ch2)
            {
                printf("first: Found: %c",temp->data);
                return;
            }
            temp=temp->nedge;
        }
    }
    */
    while(pv->nvertex != NULL && pv->data != ch1)
        pv=pv->nvertex;
    if(pv->data == ch1)
    {
        temp=pv->nedge;
        while(temp != NULL)
        {
            if(temp->data == ch2)
            {
                printf("second:Found: %c",temp->data);
                return;
            }
            temp = temp->nedge;
        }
    }
    printf("second:Not Found!");
    return;
}

void insert_vertex(struct vertex **pv ,char ch)
{
    struct vertex *p = (struct vertex *)malloc(sizeof(struct vertex));
    p->data = ch;
    p->nvertex = NULL;
    p->nedge = NULL;

    if(*pv == NULL)
    {
        *pv = p;
        printf("\n\t Vertex Inserted.");
        return;
    }
    struct vertex *temp = *pv;
    while(temp->nvertex != NULL)
    {
        //printf("%c",temp->data);
        temp = temp->nvertex;
    }
    temp->nvertex = p;
    printf("\n\t Vertex Inserted.");
}

void insert_edge(struct vertex *pv,char ch1, char ch2)
{
    struct vertex *v1 = findVertex(pv,ch1);
    struct vertex *v2 = findVertex(pv,ch2);

    if(!v1 || !v2)
    {
        printf("Vertex : %s, Not Found.",(!v1)?"Source":"Destination");
        return;
    }
    else{
        printf("Both Vertex Found.");
    }

    struct edge *p = (struct edge *)malloc(sizeof(struct edge));
    p->data = ch2;
    p->nedge = NULL;

    printf(" %c",v1->data);

    struct edge *temp = v1->nedge;
    if(temp == NULL)
    {
        v1->nedge = p;
        printf("\n\tEdge Inserted 1.");
        return;
    }
    while(temp->nedge != NULL)
    {
        temp = temp->nedge;
    }
    temp->nedge = p;
    printf("\n\tEdge Inserted 2.");
}

void display(struct vertex *pv)
{
    if(pv == NULL)
    {
        printf("\n\t Graph is Empty.");
        return;
    }
    struct edge *pe;
    while(pv != NULL)
    {
        printf("\n %c: ",pv->data);
        pe = pv->nedge;
        while(pe != NULL)
        {
            printf(" %c",pe->data);
            pe=pe->nedge;
        }
        pv=pv->nvertex;
    }
}

void remove_edge(struct vertex *pv, char ch1,char ch2)
{
    if(pv == NULL)
    {
        printf("Graph is Empty.");
        return;
    }

    struct edge *temp,*prev;

    while(pv->nvertex != NULL && pv->data != ch1)
        pv=pv->nvertex;

    if(pv->data == ch1)
    {
        temp = pv->nedge;
        if(temp->data == ch2)
        {
            pv->nedge = temp->nedge;
            free(temp);
            printf("\n first : Edge deleted.");
            return;
        }
        while(temp != NULL)
        {
            if(temp->data == ch2)
            {
                prev->nedge = temp->nedge;
                free(temp);
                printf("\n second : Edge deleted.");
                return;
            }
            prev = temp;
            temp = temp->nedge;
        }
    }

    printf("Edge Not Found!");
    return;
}

int menu()
{
    int choice;

    printf("\n -------------------------------------------");
    printf("\n\t\t Graph Operation.");
    printf("\n -------------------------------------------");

    printf("\n 1. Insert Vertex.");
    printf("\n 2. Insert Edge.");
    printf("\n 3. Find Vertex.");
    printf("\n 4. Find Edge.");
    printf("\n 5. Remove Vertex.");
    printf("\n 6. Remove Edge.");
    printf("\n 7. Display Graph.");
    printf("\n 8. Exit.");

    printf("\n\n Enter Choice: ");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    int stop = 0;
    char ch1,ch2;
    struct vertex *start = NULL;

    do{
        switch(menu())
        {
        case 1:
            printf("\n Enter vertex: ");
            scanf(" %c",&ch1);
            insert_vertex(&start,ch1);
            break;
        case 2:
            printf("\n Enter source vertex: ");
            scanf(" %c",&ch1);
            fflush(stdin);
            printf("\n Enter destination vertex: ");
            scanf(" %c",&ch2);
            insert_edge(start,ch1,ch2);
            break;
        case 3:
            printf("Enter vertex to find: ");
            scanf(" %c",&ch1);
            printf("Vertex: %c",findVertex(start,ch1)->data);
            break;
        case 4:
            printf("\n Enter source vertex: ");
            scanf(" %c",&ch1);
            fflush(stdin);
            printf("\n Enter destination vertex: ");
            scanf(" %c",&ch2);
            findEdge(start,ch1,ch2);
            break;
        case 5:
            break;
        case 6:
            printf("\n Enter source vertex: ");
            scanf(" %c",&ch1);
            fflush(stdin);
            printf("\n Enter destination vertex: ");
            scanf(" %c",&ch2);
            remove_edge(start,ch1,ch2);
            break;
        case 7:
            display(start);
            break;
        case 8:
            stop = 1;
            break;
        default:
            printf("\n Wrong Choice...\n\t Try Again");
        }
    }while(!stop);
}
