#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <string.h>

#define PATH	"/dev/simple_chrdev"


static int set(int fd, const char * str) 
{
	int ret;

	ret = write(fd, str, strlen(str));
	if(ret <= 0) {
		printf("write error\n");
		return -1;
	}

	return ret;
}


static int get(int fd, char * str, int size)
{
	int ret;
	
	ret = read(fd, str, size);
	if(ret <= 0) {
		printf("read error\n");
		return -1;
	}

	return ret;
}

int main(void)
{
	int fd;
	char buff[20] = {0};
	char aaa[] = "naruto from kernel";

	fd = open(PATH, O_RDWR);
	if (fd == -1) {
		perror(PATH);
		return -1;
	}

	set(fd, aaa);
	get(fd, buff, sizeof(buff));

	printf("%s\n", buff);

	close(fd);

	return 0;
}

