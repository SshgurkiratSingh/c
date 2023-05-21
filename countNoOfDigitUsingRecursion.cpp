// Program to count no Of digit Using recursion
#include<stdio.h>
int countDigit(int n){
    if (n == 0){
        return 0;
    }else{
        return 1 + countDigit(n/10);
    }
}

int main(){
int n;
printf("Enter the number: ");
scanf("%d",&n);
printf("The number of digit is %d",countDigit(n));
}