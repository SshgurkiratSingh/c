#include <stdio.h>

void fivex(int *ptr, int num);
void recursiveFivex(int *arr,int curr){
if (curr>=0){
    printf("5x of the %d is %d\t", arr[curr], 5 * arr[curr]);
    recursiveFivex(arr,curr-1);
}
else 
return ;
}
int main() {
    int arr[5];

    printf("Enter any 5 numbers:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }

    recursiveFivex(arr, 4);

    return 0;
}

void fivex(int *ptr, int num) {
    for (int i = 0; i < num; i++) {
        printf("5x of the %d is %d\t", ptr[i], 5 * ptr[i]);
    }
}
