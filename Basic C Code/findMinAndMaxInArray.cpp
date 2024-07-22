// Program to find minimum and maximum element in an array
#include <stdio.h>
int main(){
    int n;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    int min,max;
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
if (i==0){
    min=arr[i];
    max=arr[i];
    }
    else {
        if  (arr[i]<min){
            min=arr[i];
        }if (arr[i]>max){
            max=arr[i];
        }
    }
}
    printf("Minimum element is %d\n",min);
    printf("Maximum element is %d\n",max);}