#include<stdio.h>
#include<stdlib.h>

struct stack{
    int arr[10];
    int tos;
};

void push(struct stack *s,int v)
{
    if(s->tos == 9)
    {
        printf("\n Stack is overflow...");
        return;
    }
    s->tos++;
    s->arr[s->tos] = v;
}

int pop(struct stack *s)
{
    if(s->tos == -1)
    {
        printf("\n Stack is underflow...");
        return;
    }
    int x = s->arr[s->tos];
    s->tos--;
    return x;
}

void dfs(int p[][4], int v)
{
    struct stack s;
    s.tos = -1;
    int i;
    int status[4]={0,0,0,0};

    push(&s,v);
    while(s.tos != -1)
    {
        v=pop(&s);
        if(status[v]==0)
        {
            printf(" v[%d]  ",v);
            status[v] = 1;
        }
        for(i=3;i>=0;i--)
        {
            if(p[v][i] == 1 && status[i] == 0)
            {
                push(&s,i);
            }
        }
    }
}

int main()
{
    int path[4][4];
    int i,j,v;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            printf("\n Is Path Between v[%d] to v[%d]: ",i,j);
            scanf("%d",&path[i][j]);
        }
    }

    printf("Enter Source vertex: ");
    scanf("%d",&v);

    dfs(path,v);

    return 0;
}
