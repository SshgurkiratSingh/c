// Program to calculate fibonanchi using recusion
#include<stdio.h>
int fibDig(int a){
    if (a==0 || a==1){
        return a;
    }
    else {
        return fibDig(a-1)+fibDig(a-2);
    }
}
int main(){
    printf("%d",fibDig(9));
}