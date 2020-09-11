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

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    init_intarray_2d
 * Signature: (I)[[I
 */
JNIEXPORT jobjectArray Java_com_jni_demo_HelloWorld_init_1intarray_12d
    (JNIEnv* env, jobject obj, jint size) {
    jobjectArray result;
    jclass clsIntArray;
    jint i,j;

    //1. 获取一个int型二维数组类的引用
    clsIntArray = (*env)->FindClass(env, "[I");
    if (clsIntArray == NULL) 
    {
        return NULL;
    }

    //2. 创建一个数组对象(里面每个元素用clsIntArray表示)
    result = (*env)->NewObjectArray(env, size, clsIntArray, NULL);
    if (result == NULL) {
        return NULL;
    }

    //3. 赋值
    for (i=0; i<size; ++i) {
        jint buff[256];
        jintArray int_arr = (*env)->NewIntArray(env, size);
        if (int_arr == NULL) {
            return NULL;
        }

        for(j=0; j<size; j++) {
            buff[j] = i+j;
        }

        (*env)->SetIntArrayRegion(env, int_arr, 0, size, buff);
        (*env)->SetObjectArrayElement(env, result, i, int_arr);
        (*env)->DeleteLocalRef(env, int_arr);
    }

    return result;
}

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    CallJavaStaticMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_jni_demo_HelloWorld_CallJavaStaticMethod
  (JNIEnv *env, jclass clz) {
    jclass cls = NULL;;
    jstring str_arg = NULL;
    jmethodID method_static;

    // 1.从classpath路径下搜索NativeCallback这个类，并返回该类的Class对象
    cls = (*env)->FindClass(env, "com/jni/demo/NativeCallback");
    if (cls == NULL) {
        printf("[Error]: cannot find com/jni/demo/NativeCallback\n");
      return ;
    }

    // 2.从cls类中查找StaticCallbackMethod方法
    method_static = (*env)->GetStaticMethodID(env, cls, "StaticCallbackMethod", "(Ljava/lang/String;I)V");
    if (method_static == NULL) {
        printf ("[Error]: cannot find StaticCallbackMethod\n");
    }

    // 3.调用cls类的method_static 方法
    str_arg = (*env)->NewStringUTF(env, "This is native static call method");
    (*env)->CallStaticVoidMethod(env, cls, method_static, str_arg, 50);

    // 4. 手动删除本地引用变量
    (*env)->DeleteLocalRef(env, cls);
    (*env)->DeleteLocalRef(env, str_arg);
 }

/*
 * Class:     com_jni_demo_HelloWorld
 * Method:    CallJavaInstanceMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_jni_demo_HelloWorld_CallJavaInstanceMethod
  (JNIEnv *env, jobject obj) {
    jclass cls = NULL;;
    jstring str_arg = NULL;
    jmethodID method_constructor;
    jmethodID method_inst;
    jobject java_obj = NULL;

    // 1.从classpath路径下搜索NativeCallback这个类，并返回该类的Class对象
    cls = (*env)->FindClass(env, "com/jni/demo/NativeCallback");
    if (cls == NULL) {
        printf("[Error]: cannot find com/jni/demo/NativeCallback\n");
      return ;
    }

    // 2.从cls类中查找InstanceCallbackMethod方法
    method_inst = (*env)->GetMethodID(env, cls, "InstanceCallbackMethod", "(Ljava/lang/String;I)V");
    if (method_inst == NULL) {
        printf ("[Error]: cannot find StaticCallbackMethod\n");
        return ;
    }

    // 3. 查找NativeCallback的构造函数方法
    method_constructor = (*env)->GetMethodID(env, cls, "<init>", "()V");
    if (method_constructor == NULL) {
        printf ("[Error]: cannot find NativeCallback()\n");
        return ;
    }

    // 4. 调用NativeCallback构造函数构造对象
    java_obj = (*env)->NewObject(env, cls, method_constructor);
    if (java_obj == NULL) {
        printf ("[Error]: construct NativeCallback object failed\n");
        return ;
    }
    str_arg = (*env)->NewStringUTF(env, "This is native instance call method");
    (*env)->CallVoidMethod(env, java_obj, method_inst, str_arg, 100);

    // 4. 手动删除本地引用变量
    (*env)->DeleteLocalRef(env, cls);
    (*env)->DeleteLocalRef(env, java_obj);
    (*env)->DeleteLocalRef(env, str_arg);
}
#ifdef __cplusplus
}
#endif
