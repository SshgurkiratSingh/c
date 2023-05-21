#include <stdio.h>
#include <string.h>
int palindromeCheck(char *str,int cur,int end){
if (cur>=end){
    return 1;
}
else {
    if (str[cur]==str[end]){
        return palindromeCheck(str,cur+1,end-1);
    }else {
        return 0;
    }
}
}
int main(){
    char s[100]="harah";
    printf("%d",palindromeCheck(s,0,strlen(s)-1));
}