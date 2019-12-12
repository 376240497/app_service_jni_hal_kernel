#ifndef __SIMPLE_CDEV_H_
#define __SIMPLE_CDEV_H_

#define MAX_SIZE   1024
#define SIMPLE_MAJOR 256
#define CLASS_NAME "simple_class"
#define CHRDEV_NAME	"simple_chrdev"

struct info {
	int number;
	char author_name[20];
};

struct simple_chrdev {
         struct cdev cdev;
         char mem[MAX_SIZE];
	 char name[256];
	 struct info info;
	 int version;
	 struct mutex mutex;
};

#endif
