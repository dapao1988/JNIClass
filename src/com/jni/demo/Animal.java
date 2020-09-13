/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：Animal.java
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-09-12
*   Description   ：
*
================================================================*/

package com.jni.demo;

public class Animal {
    protected String name;

    public Animal(String name) {
        this.name = name;
        System.out.println("Animal.Animal() Called");
    }
    public String GetName() {
        System.out.println("Animal.GetName() Called");
        return "My name is :" + this.name;
    }
    public void run() {
        System.out.println("Animal.run()");
    }
}
