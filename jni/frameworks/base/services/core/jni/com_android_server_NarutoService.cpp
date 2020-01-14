/*
 * Copyright (C) 2016 The Android Open Source Project
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

#define LOG_TAG "NarutoService"

#include <android_runtime/AndroidRuntime.h>
#include <jni.h>
#include <nativehelper/JNIHelp.h>

#include <android/hardware/naruto/1.0/INaruto.h>
#include <utils/Errors.h>
#include <utils/Log.h>

namespace android {

using android::hardware::naruto::V1_0::INaruto;
using android::hardware::hidl_string;

static sp<INaruto> mNaruto;

static void init_native(JNIEnv* /* env */, jclass /* clazz */) {
    if (mNaruto != nullptr) {
        ALOGE("%s: May not initialize INaruto interface module more than once!", __FUNCTION__);
        return;
    }

    mNaruto = INaruto::getService();
    if (mNaruto == nullptr) {
        ALOGW("%s: Could not open INaruto interface", __FUNCTION__);
        return;
    }
}

static void set_native(JNIEnv * env, jclass clazz, jstring str)
{
	const char *buf = env->GetStringUTFChars(str, NULL);

	ALOGE("%s, naruto: %s", __FUNCTION__, buf);

    if (mNaruto == nullptr) {
        ALOGW("%s: Could not open INaruto interface", __FUNCTION__);
        return;
    }

	mNaruto->set(buf);

	if (buf) {
		env->ReleaseStringUTFChars(str, buf);
	}

}

static jstring get_native(JNIEnv * env, jclass clazz)
{
	jstring str = NULL;

    if (mNaruto == nullptr) {
        ALOGW("%s: Could not open INaruto interface", __FUNCTION__);
        return NULL;
    }

	mNaruto->get([&](hidl_string result){
		ALOGW("naruto@%s: %s\n", __FUNCTION__, result.c_str());
		str = env->NewStringUTF(result.c_str());
	});

	return str;
}

static const JNINativeMethod method_table[] = {
    { "NarutoInit", "()V", (void*)init_native },
    { "NarutoGet", "()Ljava/lang/String;", (void*)get_native},
    { "NarutoSet", "(Ljava/lang/String;)V", (void*)set_native},
};

int register_android_server_NarutoService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/NarutoService",
            method_table, NELEM(method_table));
}

}; // namespace android
