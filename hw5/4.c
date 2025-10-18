#include <stdio.h>
#include <stdlib.h>

int main(){
	char** string_arr = (char**)malloc(3*sizeof(char*));
	if (string_arr == NULL){
		fprintf(stderr, "Memory is not available!\n");
		return 1;
	}
	for (int i = 0; i < 3; i++){
		*(string_arr+i) = (char*)malloc(50*sizeof(char));
		if (*(string_arr) == NULL){
			fprintf(stderr, "Memory is not available!\n");
			return 1;
		}
	}
	printf("Enter 3 strings: ");
	for (int i = 0; i < 3; i++){
		scanf("%s", *(string_arr+i));
	}
	
	string_arr = (char**)realloc(string_arr, 5*sizeof(char*));
	if (string_arr == NULL){
		fprintf(stderr, "Memory is not available\n");
		return 1;
	}
	for (int i = 3; i < 5; i++){
		*(string_arr+i) = (char*)malloc(50*sizeof(char));
		if (*(string_arr+i) == NULL){
			fprintf(stderr, "Memory is not available!\n");
			return 1;
		}
	}

	printf("Enter 2 more strings: ");
	for (int i = 3; i < 5; i++){
		scanf("%s", *(string_arr+i));
	}
	
	printf("All strings: ");
	for (int i = 0; i < 5; i++){
		printf("%s ", *(string_arr+i));
	}
	printf("\n");

	for (int i = 0; i < 5; i++){
		free(*(string_arr+i));
		*(string_arr+i) = NULL;
	}
	free(string_arr);
	string_arr = NULL;
	return 0;
}
