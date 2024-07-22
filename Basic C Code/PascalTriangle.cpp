//Program to draw Pascal Triangle
#include <stdio.h>
int main(){
    int row;
    printf("Enter the number of rows: ");
    scanf("%d", &row);
    int arr[row][row];
    for(int i=0; i<row; i++){
        for (int j=0; j<i+1; j++){ 
          if (j==0 || j==i){
            arr[i][j] = 1;
          }
          else {
            arr[i][j] = arr[i-1][j-1] + arr[i-1][j];
          }
          printf("%d ", arr[i][j]);
    }
    printf("\n");
}}