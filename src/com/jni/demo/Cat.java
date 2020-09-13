/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：Cat.java
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-09-12
*   Description   ：
*
================================================================*/

package com.jni.demo;

public class Cat extends Animal {
    public Cat(String name) {
        super(name);
        this.name = name;
        System.out.println("Cat.Cat()");
    }

    @Override
    public void run() {
        System.out.println("Cat.run()");
    }

    @Override
    public String GetName() {
        System.out.println("Cat.GetName()");
        return "My name is :" + this.name;
    }
}
