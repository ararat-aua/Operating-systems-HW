#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	int* arr;
	float avg;

	printf("Enter the number of elements: ");
	scanf("%d", &n);

	arr = (int*)calloc(n, sizeof(int));
	if (arr == NULL){
		fprintf(stderr, "Memory is not available!\n");
		return 1;
	}

	printf("Array after calloc: ");
	for (int i = 0; i < n; i++){
		printf("%d ", *(arr+i));
	}
	
	printf("\nEnter %d integers: ", n);
	for (int i = 0; i < n; i++){
		scanf("%d", arr+i);
	}
	
	printf("Updated array: ");
	for (int i = 0; i < n; i++){
		printf("%d ", *(arr+i));
	}

	for (int i = 0; i < n; i++){
		avg += *(arr+i);
	}
	printf("\nAverage of the array: %f\n", avg/n);
	
	free(arr);
	arr = NULL;
	return 0;
}
