#! /bin/bash
javac src/com/jni/dynamic/*.java -d ./bin
javac -cp ./bin src/com/jni/demo/*.java -d ./bin
javah -jni -classpath ./bin -d ./src/jni com.jni.demo.HelloWorld
pushd src
#gcc -I$JAVA_HOME/include -I$JAVA_HOME/include/linux -Ijni -fPIC -shared cpp/HelloWorld.c -o ../bin/com/jni/demo/libHelloWorld.so
make clean
bear make
popd

# 或通过java.library.path 以及LD_LIBRARY_PATH
java -Djava.library.path=${HOME}/oss/demo/JNIClass/bin/com/jni/demo:${HOME}/oss/demo/JNIClass/bin/com/jni/dynamic -classpath ./bin com.jni.demo.HelloWorld
