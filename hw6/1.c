#include <stdio.h>

int main(){
	int int_var;
	char char_var;
	double double_var;
	short short_var;

	printf("Size of int variale: %ld\n", sizeof(int_var));
	printf("Adress of int variable: %p\n\n", &int_var);
	printf("Size of char variale: %ld\n", sizeof(char_var));
        printf("Adress of char variable: %p\n\n", &char_var);
	printf("Size of double variale: %ld\n", sizeof(double_var));
        printf("Adress of double variable: %p\n\n", &double_var);
	printf("Size of short variale: %ld\n", sizeof(short_var));
        printf("Adress of short variable: %p\n", &short_var);
	return 0;
}
