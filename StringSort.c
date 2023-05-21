/* Program to sort strings in dictionary order
*/
#include<stdio.h>
#include<string.h>
int main(){
	int n;
	printf("How much string you wanna enter:");
	scanf("%d",&n);
		char s[n][20];
	for (int i=0;i<n;i++){
		printf("\nEnter %d's string:",i+1);
		scanf("%s",s[i]);
	}
	char temp[50];
	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			if(strcmp(s[i], s[j]) > 0){
				strcpy(temp, s[i]);
				strcpy(s[i], s[j]);
				strcpy(s[j], temp);
				
			}

		}		}
	printf("\nwords in the ditionary order: \n");
	for(int i = 0; i < n; ++i){
		printf("%s\n",s[i]);
	}
	
}