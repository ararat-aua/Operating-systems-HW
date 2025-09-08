# include <stdio.h>

int main(){

	int arr[] = {1,2,3,4,5};
	for (int i=0; i<5; i++){
		printf("*(arr+%d)=%d\n", i, *(arr+i));
	}	

	printf("\n");
	for (int i=0; i<5; i++){
		*(arr+i) = 2 * *(arr+i);
		printf("arr[%d] = %d\n", i, arr[i]);
		printf("*(arr+%d) = %d\n", i, *(arr+i));
	}
	return 0;
}
