package com.jni.demo;

public class HelloWorld {

	public static native String hello(String name);
    public static native int add(int arg1, int arg2);
    public native double sub(float arg1, double arg2);

	public static void main(String[] args) {
        String libraryDirs = System.getProperty("java.library.path");
        System.out.println(libraryDirs);

        HelloWorld helloCls = new HelloWorld();
		String text = hello("hello world");
		System.out.println(text);

        int a = 5;
        int b = 3;
        System.out.println(add(a, b));
        System.out.println(helloCls.sub(a, b));
	}

	static {
		System.loadLibrary("HelloWorld");
	}

}
