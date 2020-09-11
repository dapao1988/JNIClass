package com.jni.demo;

/**
 * NativeCallback.java
 * 从Native Callback回Java示例
 * @author Wenbing.Wang */

public class NativeCallback {
    private static void StaticCallbackMethod(String str, int i) {
        System.out.format("NativeCallback::StaticCallbackMethod called! str=\"%s\"," +
                                " i=%d\n", str, i);
    }

    private void InstanceCallbackMethod(String str, int i) {
        System.out.format("NativeCallback::InstanceCallbackMethod called! str=\"%s\"," +
                                " i=%d\n", str, i);
    }
}
