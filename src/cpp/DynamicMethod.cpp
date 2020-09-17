/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：DynamicMethod.cpp
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-09-17
*   Description   ：
*
================================================================*/


//#include "DynamicMethod.hpp"
//

#include <jni.h>

void NativePrint() {
    printf("HelloWorld in JNI , %s, %d\n", __FILE__, __LINE__);
}

static JNINativeMethod gMethods[] ={
    {"native_print", "()V", (void*)NativePrint},
};

// JNI_OnLoad函数实现
jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_8 ) != JNI_OK) {
        return -1;
    }

    /*
     * 如果要注册，只需要两步，
     *    首先FindClass，
     *    然后RegisterNatives
     */
    char className[40] = {"com/jni/dynamic/DynamicMethod"};

    jclass clazz = (env)->FindClass( (const char*)className);
    if((env)->RegisterNatives(clazz, gMethods, 1)< 0) {
        return -1;
    }

    //一定要返回版本号，否则会出错。
    result = JNI_VERSION_1_8;
    return result;
}
