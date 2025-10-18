#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, sum;
	int* arr;

	printf("Enter the number of elementes: ");
	scanf("%d", &n);

	arr = (int*)malloc(n*sizeof(int));
	if (arr == NULL){
		fprintf(stderr, "Memory is not available!\n");
		return 1;
	}
	printf("Enter %d integers: ", n);
	for (int i = 0; i < n; i++){
		scanf("%d", arr+i);
	}
	for (int i = 0; i < n; i++){
		sum += *(arr+i);
	}
	printf("Sum of the array: %d\n", sum);
	free(arr);
	arr = NULL;
	return 0;
}
