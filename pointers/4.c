# include <stdio.h>

int main(){

	int x = 10;
	int *ptr = &x;
	int **ptrptr = &ptr;

	printf("The value of x is %d\n", x);
	printf("The value of x is %d\n", *ptr);
	printf("The value of x is %d\n", **ptrptr);
	return 0;
}
