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

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_jni_demo_HelloWorld_add (
       JNIEnv* env, jclass cls, jint f, jint d) {
    printf("arg1: %d, arg2: %d\n", f, d);
    return f+d ;
}

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    sub
 * Signature: (FD)D
 */
JNIEXPORT jdouble JNICALL Java_com_jni_demo_HelloWorld_sub (
       JNIEnv* env, jobject obj, jfloat f, jdouble d) {
    printf("arg1: %f, arg2: %lf\n", f, d);
    return f-d ;
}

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    sum_tiny
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_com_jni_demo_HelloWorld_sum_1tiny
  (JNIEnv *env, jobject obj, jintArray j_array) {
    jint i, sum = 0;
    jint *temp_array = NULL;
    jint array_len = 0;

    array_len = (*env)->GetArrayLength(env, j_array);
    
    //// 可能数组中的元素在内存中是不连续的，JVM可能会复制所有原始数据到缓冲区，然后返回这个缓冲区的指针
    //1. 可以使用系统自带的function获取数组内容
    //temp_array = (*env)->GetIntArrayElements(env,j_array,NULL);
    //2. 也可以自己分配内存然后用GetIntArrayRegion来获取内容
    temp_array = (jint*) malloc (sizeof(jint) * array_len);
    if (temp_array == NULL) {
        printf("%s %d allocate memory failed!\n", __FILE__, __LINE__);
        return 0;
    }
    printf("array_len = %d\n", array_len);
    memset((void *)temp_array, 0, array_len*sizeof(jint));

    (*env)->GetIntArrayRegion(env, j_array, 0, array_len, temp_array);

    for(i=0; i<array_len; i++) {
        sum += temp_array[i];
    }

    free(temp_array);
    return sum;
}

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    sum_large
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_com_jni_demo_HelloWorld_sum_1large
  (JNIEnv *env, jobject obj, jintArray j_array) {
    jint i, sum = 0;
    jint *temp_array = NULL;
    jint array_len = 0;
    jboolean is_copy;

    //// 可能数组中的元素在内存中是不连续的，JVM可能会复制所有原始数据到缓冲区，然后返回这个缓冲区的指针
    temp_array = (*env)->GetPrimitiveArrayCritical(env, j_array, &is_copy);
    if (temp_array == NULL) {
        printf("%s %d allocate memory failed!\n", __FILE__, __LINE__);
        return 0;
    }
    array_len = (*env)->GetArrayLength(env, j_array);
    printf("array_len = %d\n", array_len);

    (*env)->GetIntArrayRegion(env, j_array, 0, array_len, temp_array);

    for(i=0; i<array_len; i++) {
        sum += temp_array[i];
    }
    (*env)->ReleasePrimitiveArrayCritical(env,j_array, temp_array, 0);
    return sum;
}

#ifdef __cplusplus
}
#endif
