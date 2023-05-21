#include <stdio.h>

void fivex(int *ptr, int num);

int main() {
    int arr[5];

    printf("Enter any 5 numbers:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }

    fivex(arr, 5);

    return 0;
}

void fivex(int *ptr, int num) {
    for (int i = 0; i < num; i++) {
        printf("5x of the %d is %d\t", ptr[i], 5 * ptr[i]);
    }
}
