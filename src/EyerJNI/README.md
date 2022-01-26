# JNI 调用封装库

> 特别注意：别瞎跨线程使用这个库

- 首先，先在 Java 代码里新建一个类，这个类被用作本库的 Class Loader，所以建议新建一个空的类。
    ````
    package com.zzsin.eyer_camera.jni;
    
    public class EyerClazzLoader {
    }
    ````
  
- 然后写一个 JNI_OnLoad 函数，把本库给初始化了
    ````
    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM * vm, void * reserved)
    {
        EyerLog("JavaVM GetEnv Success\n");
    
        JNIEnv * env = nullptr;
        if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
            EyerLog("JavaVM GetEnv Fail\n");
            return -1;
        }
    
        Eyer::EyerJNIEnvManager::Init(vm, env, "com/zzsin/eyer_camera/jni/EyerClazzLoader");
    
        return JNI_VERSION_1_6;
    }
    ````

