/*program to remove 'C' from the entered words */
#include<stdio.h>
int main(){
	char str[100];
	printf("Enter a String:");
	scanf("%s",str);
	for(int i=0;i<100;i++){
		if(str[i]=='c'){
			str[i]=' ';
		}
	}
	printf("%s",str);
	
	
}
