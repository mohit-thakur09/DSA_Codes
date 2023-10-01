#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    char arr[10];
    int tos;
}stack;

void push(stack *s, int x){
    if(s->tos == -9){
        printf("Stack overflow \n");
        return;
    }
    s->tos++;
    s->arr[s->tos]=x;
}

int pop(stack *s){

    int x;

    if(s->tos == -1){
        printf("Stack is underflow \n");
        return 0;
    }
    x = s->arr[s->tos];
    s->tos--;
    return x;
}

int isOprend(char ch){
    return ((ch>=48 && ch<=57) || (ch>=97 && ch<= 122) || (ch>=57 && ch<=83));
}

int isEmpty(s){
    return(s==-1);
}

int precedence(char op1, char op2){

    if(op2=='$')
        return 0;
    else if(op1=='$')
        return 1;
    else if(op2=='*' || op2=='/' || op2=='%' )
        return 0;
    else if(op1=='*' || op1=='/' || op1=='%' )
        return 1;
    else if(op2=='+' || op2=='-')
        return 0;
    else
        return 1;

}

void convert(char *infix, char *postfix){

    stack s;
    s.tos = -1;
    int i, j = 0;
    char ch;

    for(i=0; infix[i] != '\0' ;i++){
        ch = infix[i];
        if(isOprend(ch)==1){
            postfix[j]=ch;
            j++;
        }
        else{
            while(isEmpty(s.tos)==0){
                if(precedence(ch,s.arr[s.tos])==1){
                    break;
                }
                postfix[j]=pop(&s);
                j++;
            }
            push(&s,ch);
        }
    }
    while(isEmpty(s.tos)==0){
        postfix[j]=pop(&s);
        j++;
    }
    postfix[j]='\0';
    return;

}

int main()
{
    char infix,postfix;

    printf("Enter Valid Infix Expression: ");
    scanf("%s",&infix);

    convert(&infix,&postfix);

    printf("\nConversion of infix to postfix is: ");
    puts(&postfix);
    return 0;
}
