#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int fd;
	if ((fd=open("numbers.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644))==-1){
		perror("Open");
		exit(1);
	}
	char buf[3];
	int n_wr;
	for (int i=1; i<11; i++){
		if(i==10){
			buf[0]='1';
			buf[1]='0';
			buf[2]='\n';
			n_wr = 3;
		}
		else{
			buf[0] = (char)i+'0';
			buf[1] = '\n';
		       	n_wr = 2;	
		}
		if(write(fd, buf, n_wr) == -1){
			perror("Write");
			exit(1);
		}
	}
	if(close(fd) == -1){
		perror("Close");
		exit(1);
	}
	
	if((fd=open("numbers.txt", O_RDWR))==-1){
		perror("Open");
		exit(1);
	}
	
	int num_new_lines = 0;
	while(num_new_lines!=3){
		if(read(fd, buf, 1)==-1){
			perror("Read");
			exit(1);
		}
		if(buf[0]=='\n'){
			num_new_lines++;
		}
	}
	
	int cur_pos = lseek(fd, 0, SEEK_CUR);
	if (cur_pos==-1){
		perror("Lseek");
		exit(1);
	}

	if(lseek(fd, cur_pos+2, SEEK_SET) == -1){
		perror("Lseek");
		exit(1);
	}
	
	char tmp_buf[100];
	int n_rd = read(fd, tmp_buf, 100);
	if (n_rd==-1){
		perror("Read");
		exit(1);
	}

	if(lseek(fd, cur_pos, SEEK_SET)==-1){
		perror("Lseek");
		exit(1);
	}
	if(write(fd, "100\n", 4)==-1){
		perror("Write");
		exit(1);
	}
	if(write(fd, tmp_buf, n_rd)==-1){
		perror("Write");
		exit(1);
	}
	
	if(lseek(fd, 0, SEEK_SET)==-1){
		perror("Lseek");
		exit(1);
	}
	n_rd = -1;
	while(n_rd!=0){
		if((n_rd=read(fd, tmp_buf, 100))==-1){
			perror("Read");
			exit(1);
		}
		if(write(1, tmp_buf, n_rd)==-1){
			perror("Write");
			exit(1);
		}
	}
	if(close(fd)==-1){
		perror("Close");
		exit(1);
	}

	return 0;
}
