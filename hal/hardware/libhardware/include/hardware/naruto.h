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

#ifndef _HARDWARE_NARUTO_H
#define _HARDWARE_NARUTO_H

#include <hardware/hardware.h>

__BEGIN_DECLS

#define NARUTO_HARDWARE_MODULE_ID "naruto"
#define NARUTO_HARDWARE_DEVICE_ID "naruto"

struct naruto_module_t { 
     struct hw_module_t commom;
};

struct naruto_device_t {

    struct hw_device_t common;

    int (*set)(struct naruto_device_t * dev, const char *str);

    int (*get)(struct naruto_device_t * dev, char * str, int size);

	int fd;

};

static inline int naruto_open(const struct hw_module_t* module, struct naruto_device_t** device)
{
    return module->methods->open(module, NARUTO_HARDWARE_DEVICE_ID, TO_HW_DEVICE_T_OPEN(device));
}

__END_DECLS

#endif  // _HARDWARE_NARUTO_H
