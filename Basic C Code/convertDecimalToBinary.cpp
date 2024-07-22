// Program to convert Decimal to Binary
#include<stdio.h>
int decToBin(int n){
    if (n==0){
        return 0;
    }
    else{return  n%2 + 10*decToBin(n/2);
}}
int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    printf("Binary of %d is %d\n",n,decToBin(n));
}