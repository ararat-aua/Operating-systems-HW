# include <stdio.h>

int main(){
	int x = 10;
	int *ptr_x = &x;
	printf("The adress of x is %p\n", &x);
	printf("The adress of x is %p\n", ptr_x);
	*ptr_x = 20;
	printf("Value of x = %d\n", x);
	return 0;
}
