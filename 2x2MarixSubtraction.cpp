// Program to subtract two matrices
 #include<stdio.h>
 int main()
 {
 	int a[2][2],b[2][2],sub[2][2],i,j;
 	
 	printf("\n Enter the elements of the first matrix:\n");
 	for(i=0;i<2;i++)
 	{
 		for(j=0;j<2;j++){
 		scanf("%d",&a[i][j]);
	 }
 }
 printf("\n Enter the elements of second matrix:\n");
 for(i=0;i<2;i++)
 {
 	for(j=0;j<2;j++)
 	{
 		scanf("%d",&b[i][j]);
	 }
 }
 
 for(i=0;i<2;i++)
 {
 	for(j=0;j<2;j++)
 	{
 		sub[i][j]=a[i][j]-b[i][j];
 		
	 }
 }
 printf("\n Sub of the matrices:\n");
 for(i=0;i<2;i++)
 {
 	for(j=0;j<2;j++)
 {
 	printf("%d\t",sub[i][j]);
 	
 }
 printf("\n");
 }
}
