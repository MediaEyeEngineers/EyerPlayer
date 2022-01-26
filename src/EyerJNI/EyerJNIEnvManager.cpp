#include "EyerJNIEnvManager.hpp"

#include <jni.h>

namespace Eyer
{
    JavaVM * EyerJNIEnvManager::vm = nullptr;
    jobject EyerJNIEnvManager::clazzLoaderObject = nullptr;
    jmethodID EyerJNIEnvManager::findClassMethod = nullptr;

    int EyerJNIEnvManager::Init(JavaVM * _vm, JNIEnv * env, const EyerString & clazzLoaderName)
    {
        jclass eyerClazzLoader = env->FindClass(clazzLoaderName.str);
        jclass eyerClazzLoaderClazz = env->GetObjectClass(eyerClazzLoader);

        auto classLoaderClass = env->FindClass("java/lang/ClassLoader");
        auto getClassLoaderMethod = env->GetMethodID(eyerClazzLoaderClazz, "getClassLoader","()Ljava/lang/ClassLoader;");

        clazzLoaderObject = env->NewGlobalRef(env->CallObjectMethod(eyerClazzLoader, getClassLoaderMethod));
        findClassMethod = env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");

        vm = _vm;

        return 0;
    }

    EyerJNIEnv EyerJNIEnvManager::AttachCurrentThread()
    {
        JNIEnv * env = nullptr;
        int status = EyerJNIEnvManager::vm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (status < 0) {
            EyerJNIEnvManager::vm->AttachCurrentThread((JNIEnv **)&env, NULL);
        }

        EyerJNIEnv jniEnv(env);
        return jniEnv;
    }

    int EyerJNIEnvManager::DetachCurrentThread()
    {
        EyerJNIEnvManager::vm->DetachCurrentThread();
        return 0;
    }

    jclass EyerJNIEnvManager::FindClazz(EyerJNIEnv * _env, const char * name)
    {
        JNIEnv * env = _env->env;
        return static_cast<jclass>(env->CallObjectMethod(clazzLoaderObject, findClassMethod, env->NewStringUTF(name)));
    }
}