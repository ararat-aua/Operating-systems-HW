#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char src_file_path[100];
	char dst_file_path[100];
	char buf[10];
	int src_fd, dst_fd;
	
	printf("Enter source file path: ");
	scanf("%s", src_file_path);
	src_fd = open(src_file_path, O_RDONLY);
	if (src_fd==-1){
		perror("Open");
		exit(1);
	}
	
	printf("Enter destinatoin file path: ");
	scanf("%s", dst_file_path);
	dst_fd = open(dst_file_path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (dst_fd == -1){
		perror("Open");
		exit(1);
	}

	int num_rd = -1;
	int num_wr = -1;
	int total = 0;
	while (num_rd != 0){
		num_rd = read(src_fd, buf, sizeof(buf));
		if (num_rd == -1){
			perror("Read");
			exit(2);
		}
		num_wr = write(dst_fd, buf, num_rd);
		if (num_wr == -1){
			perror("Write");
			exit(2);
		}
		total += num_wr;
	}
	if(close(src_fd)==-1){
		perror("Close");
		exit(3);
	}
	if(close(dst_fd)==-1){
		perror("Close");
		exit(3);
	}
	printf("Total bytes read: %d\n", total);
	return 0;
}
