#include "jni.h"   // jni 开发必须的 头文件
#include <string.h>
#include <android/log.h>

#include "include/dmsg.h"
#include "sys_rs485.h"

extern "C" {
jint Java_com_dnake_demo485_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    uint8_t data[] = {0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03};
    int sz = sizeof(data);
    sys_rs485.start();

    while (1) {
        {
            fprintf(stderr, "--> ");
            for(int i=0; i<sz; i++)
                fprintf(stderr, "%02X ", data[i]);
            fprintf(stderr, "\n");
        }
        int len = sys_rs485.dtx(data, sz);
        __android_log_print(ANDROID_LOG_INFO, "Test485", "--> TX %02X ... (%d)", data[0], len);
        sleep(5);
    }
    return 0;
}
}