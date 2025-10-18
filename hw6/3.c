#include <stdio.h>
#include <stddef.h>

struct MyStruct1 {
	char a;
	int b;
	double c;
};

#pragma pack(push, 1)
struct MyStruct2 {
        char a;
        int b;
        double c;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct MyStruct3 {
        char a;
        int b;
        double c;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct MyStruct4 {
        char a;
        int b;
        double c;
};
#pragma pack(pop)

int main(){
	struct MyStruct1 s1;
	struct MyStruct2 s2;
	struct MyStruct3 s3;
	struct MyStruct4 s4;

	printf("Struct without pack:\n");
	printf("Sizeof struct = %zu\n", sizeof(struct MyStruct1));
	printf("&s.a = %p\n", &s1.a);
	printf("&s.b = %p\n", &s1.b);
	printf("&s.c = %p\n", &s1.c);
	printf("a offset = %zu\n", offsetof(struct MyStruct1, a));
	printf("b offset = %zu\n", offsetof(struct MyStruct1, b));
	printf("c offset = %zu\n\n", offsetof(struct MyStruct1, c));
	
	printf("Struct with pack(1):\n");
        printf("Sizeof struct = %zu\n", sizeof(struct MyStruct2));
        printf("&s.a = %p\n", &s2.a);
        printf("&s.b = %p\n", &s2.b);
        printf("&s.c = %p\n", &s2.c);
        printf("a offset = %zu\n", offsetof(struct MyStruct2, a));
        printf("b offset = %zu\n", offsetof(struct MyStruct2, b));
        printf("c offset = %zu\n\n", offsetof(struct MyStruct2, c));

	printf("Struct with pack(2):\n");
        printf("Sizeof struct = %zu\n", sizeof(struct MyStruct3));
        printf("&s.a = %p\n", &s3.a);
        printf("&s.b = %p\n", &s3.b);
        printf("&s.c = %p\n", &s3.c);
        printf("a offset = %zu\n", offsetof(struct MyStruct3, a));
        printf("b offset = %zu\n", offsetof(struct MyStruct3, b));
        printf("c offset = %zu\n\n", offsetof(struct MyStruct3, c));

	printf("Struct with pack(4):\n");
        printf("Sizeof struct = %zu\n", sizeof(struct MyStruct4));
        printf("&s.a = %p\n", &s4.a);
        printf("&s.b = %p\n", &s4.b);
        printf("&s.c = %p\n", &s4.c);
        printf("a offset = %zu\n", offsetof(struct MyStruct4, a));
        printf("b offset = %zu\n", offsetof(struct MyStruct4, b));
        printf("c offset = %zu\n\n", offsetof(struct MyStruct4, c));
	return 0;
}
