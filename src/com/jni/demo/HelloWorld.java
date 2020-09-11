package com.jni.demo;

public class HelloWorld {

	public static native String hello(String name);
    public static native int add(int arg1, int arg2);
    public native double sub(float arg1, double arg2);

    public native int sum_tiny(int[] array);
    public native int sum_large(int[] array);

    public native int[][] init_intarray_2d(int size);

	public static void main(String[] args) {
        String libraryDirs = System.getProperty("java.library.path");
        System.out.println(libraryDirs);

        HelloWorld hello_cls = new HelloWorld();
		String text = hello("hello world");
		System.out.println(text);

        int a = 5;
        int b = 3;
        /**
         * static native function */
        System.out.println(add(a, b));
        /**
         * inner native function */
        System.out.println(hello_cls.sub(a, b));


        /**
         * sum a tiny array, doesn't care copy in jni */
        final int SMALL_NUM = 10;
        int[] array = new int[SMALL_NUM];
        for (int i=0; i<10; i++) {
            array[i] = i;
        }
        int sum = hello_cls.sum_tiny(array);
        System.out.println("sum_tiny: " + sum);

        /**
         * sum a large array, should not copy in jni */
        final int LARGE_NUM = 10000;
        int[] array_large = new int[LARGE_NUM];
        for (int i=0; i<LARGE_NUM; i++) {
            array_large[i] = i;
        }
        int sum_large = hello_cls.sum_large(array_large);
        System.out.println("sum_large: " + sum_large);

        /**
         * initialized a 2d-array */
        int[][] int_array_2d = hello_cls.init_intarray_2d(4);
        System.out.println("2d-array is:");
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                System.out.format("%d ", int_array_2d[i][j]);
            }
            System.out.format("\n");
        }

	}

	static {
		System.loadLibrary("HelloWorld");
	}

}
