#include "math_utils.h"
#include <stdio.h>

int main(){
	int a, res;
	printf("Enter the number, please: ");
	scanf("%d", &a);
	res = square(a);
	printf("The result is %d\n", res);
	return 0;
}
