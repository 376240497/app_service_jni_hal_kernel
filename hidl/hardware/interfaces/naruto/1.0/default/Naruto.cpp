#define LOG_TAG "NarutoService"

#include <inttypes.h>

#include <log/log.h>

#include <hardware/hardware.h>
#include <hardware/naruto.h>

#include "Naruto.h"


namespace android {
namespace hardware {
namespace naruto {
namespace V1_0 {
namespace implementation {

Naruto::Naruto(struct naruto_device_t *device) : mDevice(device) {}

// Methods from ::android::hardware::naruto::V1_0::INaruto follow.
Return<void> Naruto::get(get_cb _hidl_cb) {

	int ret;
	char buf[128];
	::memset(buf, 0, 128);
	
	ret = mDevice->get(mDevice, buf, sizeof(buf));
	if (ret == -1) {
        ALOGE(" get on command failed : %s", strerror(-ret));
        //return Status::UNKNOWN_ERROR;
	} else {
		hidl_string result(buf);
		_hidl_cb(result);
	}

    return Void();
}

Return<void> Naruto::set(const hidl_string& buf) {

	int ret;
	char str[128];
	::memset(str, 0, 128);
	::snprintf(str, 128, "%s", buf.c_str());

	ret = mDevice->set(mDevice, str);
	if (ret == -1) {
        ALOGE("set on command failed : %s", strerror(-ret));
        //return Status::UNKNOWN_ERROR;
	} 

    return Void();
}


//JNI层通过INaruto::getService() --> 最终调用到HIDL_FETCH_INaruto
INaruto* HIDL_FETCH_INaruto(const char* /* name */) {
	struct naruto_device_t * device = nullptr;
	const struct hw_module_t *module = nullptr;

	//通过ID查找到对应的HAL lib模块
	int ret = hw_get_module(NARUTO_HARDWARE_MODULE_ID, &module);

	if (ret == 0) {

		//在通过module获取到HAL device, 通过device可以调用HAL中的方法
		ret = naruto_open(module, &device);

		if (ret != 0) {
			ALOGE("naruto device open failed: %d\n", ret);
		}
	} else {
		ALOGE("naruto module open failed: %d\n", ret);
	}

	if (ret == 0) {
		//返回一个INaruto对象，JNI就可以通过INaruto对象调用到HIDL中实现的方法
    	return new Naruto(device);
	} else {
		ALOGE("failed to open naruto hal\n");
		return nullptr;
	}

}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace naruto
}  // namespace hardware
}  // namespace android
