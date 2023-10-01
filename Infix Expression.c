#include<stdio.h>
int isOperand(char ch){
    return (48<ch)&&(ch<57)?1:0;
}

int main(){
    printf("%d",isOperand('e'));
}
