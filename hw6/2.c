#include <stdio.h>
#include <stddef.h>

struct MyStruct1{
	char a;
	int b;
	double c;
};
struct MyStruct2{
	char a;
	double c;
	int b;
};

int main(){
	struct MyStruct1 s1;
	struct MyStruct2 s2;

	printf("MyStruct1 information:\n");
	printf("Sizeof(MyStruct1) = %zu\n", sizeof(struct MyStruct1));
	printf("&s1.a = %p\n", &s1.a);
	printf("&s1.b = %p\n", &s1.b);
	printf("&s1.c = %p\n\n", &s1.c);
	printf("a offset = %zu\n", offsetof(struct MyStruct1, a));
	printf("b offset = %zu\n", offsetof(struct MyStruct1, b));
	printf("c offset = %zu\n\n", offsetof(struct MyStruct1, c));
	
	printf("MyStruct2 information:\n");
	printf("Sizeof(MyStruct2) = %zu\n", sizeof(struct MyStruct2));
        printf("&s2.a = %p\n", &s2.a);
        printf("&s2.b = %p\n", &s2.b);
        printf("&s2.c = %p\n\n", &s2.c);
	printf("a offset = %zu\n", offsetof(struct MyStruct2, a));
        printf("b offset = %zu\n", offsetof(struct MyStruct2, b));
        printf("c offset = %zu\n\n", offsetof(struct MyStruct2, c));
	return 0;
}
