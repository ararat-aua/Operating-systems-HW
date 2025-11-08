#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int min(int a, int b){
	return a<b?a:b;
}
void close_files(int fd1, int fd2){
	if(close(fd1)==-1){
		perror("Close");
		exit(1);
	}
	if(close(fd2)==-1){
		perror("Close");
		exit(1);
	}
}

int main(){
	int fd1, fd2;
	char file1[100];
	char file2[100];

	printf("Enter path of first file: ");
	scanf("%s", file1);
	if((fd1=open(file1, O_RDONLY))==-1){
		perror("Open");
		exit(1);
	}
	printf("Enter path of second file: ");
	scanf("%s", file2);
	if((fd2=open(file2, O_RDONLY))==-1){
		perror("Open");
		exit(1);
	}
	
	char buf1[10];
	char buf2[10];
	int n_rd1=-1;
	int n_rd2=-1;
	int total = 0;
	while(n_rd1!=0){
		if((n_rd1=read(fd1, buf1, sizeof(buf1)))==-1){
			perror("Write");
			exit(1);
		}
		if((n_rd2=read(fd2, buf2, sizeof(buf2)))==-1){
			perror("Write");
			exit(1);
		}
		if(n_rd1!=n_rd2){
			for(int i=0; i<min(n_rd1, n_rd2); i++){
				if(buf1[i]!=buf2[i]){
					printf("Files differ at byte %d\n", total);
					close_files(fd1, fd2);	
					exit(2);
				}
				total++;
			}
			printf("Files differ at byte %d\n", total);
			close_files(fd1, fd2);
			exit(2);		
		}
		else{
			for(int i=0; i<n_rd1; i++){
				if(buf1[i]!=buf2[i]){
					printf("Files differ at byte %d\n", total);
					close_files(fd1, fd2);
					exit(2);
				}
				total++;
			}
		}
	}
	printf("Files are identical!\n");
	return 0;

}
