#include<stdio.h>

typedef struct stack{
    char arr[30];
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

int isOperend(char ch){
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


void convert(char *infix, char *postfix)
{
    stack s;
    s.tos = -1;
    char ch;
    int i,j=0;

    //a*(b+c-d)/(f*g+e)$h

    for(i=0;infix[i];i++)
    {
        ch=infix[i];
        if(isOperend(ch)==1)
        {
            postfix[j]=ch;
            j++;
        }
        else
        {
            if(ch=='(')
            {
                    push(&s,ch);
            }
            else if(ch==')')
            {
                while(s.arr[s.tos] != '(')
                {
                    postfix[j]=pop(&s);
                    j++;
                }
                pop(&s);
            }
            else
            {
                while(isEmpty(s.tos)==0)
                {
                    if(precedence(ch,s.arr[s.tos])==1)
                    {
                        break;
                    }
                    postfix[j]=pop(&s);
                    j++;
                }
                push(&s,ch);
            }
        }
    }
        /*else
        {
            while(1)
            {
                if(isEmpty(s.tos)==0)
                {
                    if( (ch==')') || (ch=='(') || (s.arr[s.tos]=='(') || (precedence(ch,s.arr[s.tos]) == 1))
                    {
                        if(ch==')')
                        {
                            while(pop(&s) != '(')
                            {
                                postfix[j]=pop(&s);
                                j++;
                            }
                            break;
                        }
                        push(&s,ch);
                    }
                    else
                    {
                        postfix[j]=pop(&s);
                        j++;
                        break;
                    }
                }
                else
                {
                    push(&s,ch);
                    break;
                }
            }
        }
    }*/
    while(isEmpty(s.tos)==0)
    {
        postfix[j]=pop(&s);
        j++;
    }
    postfix[j]='\0';
    return;
}

int main()
{
    char infix[30],postfix[30];

    printf("\n Enter the valid Infix: ");
    scanf("%s",&infix);

    convert(infix,postfix);

    printf("\n Solution of Infix to Postfix: ");
    printf("%s \n",postfix);
    return 0;
}
