/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/naruto.h>

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stddef.h>

#include <log/log.h>

#define DEVICE_PATH  "/dev/simple_chrdev"

static int naruto_set(struct naruto_device_t * dev, const char *str)
{
	int ret;
	ret = write(dev->fd, str, strlen(str));
	if(ret <= 0) {
		ALOGE("%s: write error\n", __func__);
		return -1;
	}

	return ret;
}

static int naruto_get(struct naruto_device_t * dev, char * str, int size)
{
	int ret;
	
	ret = read(dev->fd, str, size);
	if(ret <= 0) {
		ALOGE("%s: read error\n", __func__);
		return -1;
	}

	return ret;
}

static int naruto_device_close(struct hw_device_t * device)
{
	struct naruto_device_t * dev = (struct naruto_device_t *)device;

	if (dev) {
		close(dev->fd);
		free(dev);
	}

	return 0;
}


static int naruto_device_open(const struct hw_module_t* module, 
	const char* id, struct hw_device_t** device)
{
	struct naruto_device_t *dev;

	dev = (struct naruto_device_t *) malloc(sizeof(struct naruto_device_t));
	
	if(!dev) {
		ALOGE("%s naruto failed to alloc space\n", __func__);
		return -EFAULT;
	}

	memset(dev, 0, sizeof(struct naruto_device_t));
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (hw_module_t *)module;
	dev->common.close = naruto_device_close;

	dev->get = naruto_get;
	dev->set = naruto_set;

	if ((dev->fd = open(DEVICE_PATH, O_RDWR)) == -1) {
		ALOGE("%s: OPEN /dev/simple_chrdev failed, err: %s\n", __func__, strerror(errno));
		free(dev);
		return -EFAULT;
	}

	*device = (hw_device_t *) dev;
	
	ALOGE("%s: OPEN /dev/simple_chrdev success", __func__);

	return 0;

}


static struct hw_module_methods_t naruto_module_methods = {
    .open = naruto_device_open,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    	.tag = HARDWARE_MODULE_TAG,
    	.version_major = 1,
    	.version_minor = 0,
    	.id = NARUTO_HARDWARE_MODULE_ID,
    	.name = "Default naruto HAL",
    	.author = "ye.liao",
    	.methods = &naruto_module_methods,
};
