#include <stdio.h>
#include <stdlib.h>
int min(int a, int b){
	if (a < b)
		return a;
	return b;
}
int max(int a, int b){
	if (a < b)
		return b;
	return a;
}

int main(){
	int n, lowest, highest;
	int* arr;

	printf("Enter the numer of students: ");
	scanf("%d", &n);
	arr = (int*)malloc(n*sizeof(int));
	if (arr == NULL){
		fprintf(stderr, "Memoery is not available\n");
		return 1;
	}
	printf("Enter the grades: ");
	for (int i = 0; i < n; i++){
		scanf("%d", arr+i);
	}
	lowest = *arr;
	highest = *arr;

	for (int i = 0; i < n; i++){
		lowest = min(lowest, *(arr+i));
		highest = max(highest, *(arr+i));
	}

	printf("Highest grade: %d\n", highest);
	printf("Lowest grade: %d\n", lowest);
	
	free(arr);
	arr = NULL;
	return 0;
}
