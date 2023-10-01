#include<stdio.h>

typedef struct Stack{
    int arr[5];
    int tos;
}Stack;

void push(Stack *s,int x){

    if(s->tos == 4){
        printf("\n Stack is Overflow...\n");
        return;
    }
    s->tos++;
    s->arr[s->tos]=x;
    printf("\n %d Is successfully PUSH'ed in Stack.\n",x);
}

int pop(Stack *s){

    if(s->tos == -1){
        printf("\n Stack is Underflow...");
        return -1;
    }
    int x = s->arr[s->tos];
    s->tos--;
    return x;
}

void peep(Stack *s){

    if(s->tos == -1){
        printf("\n Stack is Underflow...\n");
        return;
    }
    printf("\n\t Top most value of Stack is : %d",s->arr[s->tos]);
}

void traverse(Stack *s){
    int i;
    if(s->tos == -1){
        printf("\n Stack is Underflow...\n");
        return;
    }
    for(i=0;i<=(s->tos);i++){
        printf("%d  ",s->arr[i]);
    }
    printf("\n");
}

int menu(){
    int op;
    printf("\n\t\t Stack Operations \n");

    printf("\n 1. PUSH");
    printf("\n 2. POP");
    printf("\n 3. PEEP");
    printf("\n 4. Traverse");
    printf("\n 5. Exit");

    printf("\n\n Select Option: ");
    scanf("%d",&op);
    return op;
}

int main(){
    int x;
    Stack s;
    s.tos=-1;

    while(1){
    switch(menu())
        {
            case 1:
                printf("Enter Number for Push : ");
                scanf("%d",&x);
                push(&s,x);
                break;
            case 2:
                x = pop(&s);
                if(x == -1){
                    printf("\n Nothing can be popped.\n");
                }else{
                    printf("Popped value is: %d\n",x);
                }
                break;
            case 3:
                peep(&s);
                break;
            case 4:
                traverse(&s);
                break;
            case 5:
                exit(0);
            default:
                printf("You have selected the WRONG value...\n\n");
        }
    }
}
