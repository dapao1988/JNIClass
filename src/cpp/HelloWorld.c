/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：HelloWorld.c
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-09-10
*   Description   ：
*
================================================================*/

// HelloWorld.c

#include "com_jni_demo_HelloWorld.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    hello
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_jni_demo_HelloWorld_hello(
		JNIEnv *env, jclass cls, jstring j_str)
{
	const char *c_str = NULL;
	char buff[128] = { 0 };
	c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
	if (c_str == NULL)
	{
		printf("out of memory.\n");
		return NULL;
	}
	printf("Java Str:%s\n", c_str);
	sprintf(buff, "hello %s", c_str);
        (*env)->ReleaseStringUTFChars(env, j_str, c_str);
	return (*env)->NewStringUTF(env, buff);
}

JNIEXPORT jint JNICALL Java_com_jni_demo_HelloWorld_add (
       JNIEnv* env, jclass cls, jint f, jint d) {
    printf("arg1: %d, arg2: %d\n", f, d);
    return f+d ;
}

JNIEXPORT jdouble JNICALL Java_com_jni_demo_HelloWorld_sub (
       JNIEnv* env, jobject obj, jfloat f, jdouble d) {
    printf("arg1: %f, arg2: %lf\n", f, d);
    return f-d ;
}

#ifdef __cplusplus
}
#endif
