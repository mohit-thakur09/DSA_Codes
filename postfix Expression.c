#include<stdio.h>
#include<math.h>

//find Postfix Expression ans...
// 56*2/4-7+
// 52$7*2/8+

typedef struct Stack{
    float arr[10];
    int tos;
}Stack;

int isOperand(char ch){
     return (48<ch)&&(ch<57)?1:0;
}

void push(Stack *s,float num){
    if(s->tos == 9){
        printf("stack is overflow\n");
    }
    s->tos++;
    s->arr[s->tos]=num;
}

float pop(Stack *s){
    float x;
    if(s->tos == -1){
        printf("stack is underflow\n");
    }
     x = s->arr[s->tos];
     s->tos--;
     return x;
}

float eval(float op1,float op2, char ch){
    switch (ch){
    case '+':
        return (op1+op2);
    case '-':
        return (op1-op2);
    case '*':
        return (op1*op2);
    case '/':
        return (op1/op2);
    case '$':
        return pow(op1,op2);
    //case '%':
        //return (op1%op2);
    }
}

float solveExpression(char post[]){

    Stack s;
    s.tos = -1;
    char ch;
    int i;
    float op1,op2,cal;

    for(i=0; post[i]!='\0'; i++){
        ch = post[i];
        if(isOperand(ch)==1){
            push(&s,ch-48);
        }else{
            op2 = pop(&s);
            op1 = pop(&s);
            cal =  eval(op1,op2,ch);
            push(&s,cal);
        }
    }
    return pop(&s);
}

int main(){

    float ans;
    char postfix[10];

    printf("Enter a Postfix Expression: ");
    gets(postfix);

    ans = solveExpression(postfix);
    printf("Ans of Postfix Expression: %f \n",ans);

    return 0;
}
