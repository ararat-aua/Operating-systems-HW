# include <stdio.h>

int main(){
	char str[] = "Hello";
	char *first = str;
	for (int i=0; i<5; i++){
		printf("str[%d] = %c\n", i, *(first+i));
	}
	int count = 0;
	for (int i=0; ;i++){
		if (*(first+i)=='\0'){
			break;
		}
		count++;
	}	
	printf("Number of characters is %d\n", count);
	return 0;
}
