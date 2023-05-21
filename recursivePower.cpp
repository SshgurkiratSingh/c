//Program to calculate power of a number using recursion
#include <stdio.h>
int powerCalculator(int a,int b){
    if (b==0){
        return 1;
    }
    else {
        return a*powerCalculator(a,b-1);

    }
}
int main(){
    int a=2;
    int b=4;
    printf("%d",powerCalculator(a,b));
}