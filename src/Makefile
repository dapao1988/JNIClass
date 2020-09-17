all:
	 gcc -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -Ijni -fPIC -shared cpp/HelloWorld.c -o ../bin/com/jni/demo/libHelloWorld.so
	 gcc -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -Ijni -fPIC -shared cpp/DynamicMethod.cpp -o ../bin/com/jni/dynamic/libDynamicMethod.so

clean:
	 find ../bin -name "*.so" -print0 | xargs -i -0 rm {} 
