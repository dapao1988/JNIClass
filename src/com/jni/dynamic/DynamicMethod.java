/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：Animal.java
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-09-12
*   Description   ：
*
================================================================*/

package com.jni.dynamic;

public class DynamicMethod {

    private native void native_print();
    public void PrintHello() {
        System.out.println("DynamicMethod PrintHello called in Java");

        native_print();
    }
}
