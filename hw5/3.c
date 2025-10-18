#include <stdio.h>
#include <stdlib.h>

int main(){
	int *arr;
	arr = (int*)malloc(10*sizeof(int));
	if (arr == NULL){
		fprintf(stderr, "Memory is not available!\n");
		return 1;
	}
	printf("Enter 10 integers: ");
	for (int i = 0; i < 10; i++){
		scanf("%d", arr+i);
	}
	
	arr = (int*)realloc(arr, 5*sizeof(int));
	if (arr == NULL){
		fprintf(stderr, "Could not reallocate memory!\n");
		return 1;
	}
	printf("Array after resizing: ");
	for (int i = 0; i < 5; i++){
		printf("%d ", *(arr+i));
	}
	printf("\n");
	free(arr);
	arr = NULL;
	return 0;
}
