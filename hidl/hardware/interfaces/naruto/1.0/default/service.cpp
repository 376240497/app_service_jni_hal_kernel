# define LOG_TAG "android.hardware.naruto@1.0-service"

# include <hidl/HidlTransportSupport.h>

# include <android/hardware/naruto/1.0/INaruto.h>

# include <hidl/LegacySupport.h>

# include "Naruto.h"

#if USE_BINDERIZED
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
using android::hardware::naruto::V1_0::implementation::Naruto;
#else
using android::hardware::defaultPassthroughServiceImplementation;
#endif

using android::hardware::naruto::V1_0::INaruto;


int main() {
#if USE_BINDERIZED
    android::sp<INaruto> service = new Naruto();
    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (service->registerAsService() != android::OK) {
        exit(1);
    }
    joinRpcThreadpool();
#else
    return defaultPassthroughServiceImplementation<INaruto>();
#endif
}
