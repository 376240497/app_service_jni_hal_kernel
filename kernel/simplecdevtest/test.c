#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <string.h>

#define PATH	"/dev/simple_chrdev"

int main(void)
{
	int fd;
	char buff[20] = {0};
	char str[20] = "I am from kernel";

	fd = open(PATH, O_RDWR);
	if (fd == -1) {
		perror(PATH);
		return -1;
	}

	write(fd, str, strlen(str));
	
	read(fd, buff, 20);

	printf("%s\n", buff);

	close(fd);

	return 0;
}
