#ifndef EYERCAMERAANDROID_EYERJNIENVMANAGER_HPP
#define EYERCAMERAANDROID_EYERJNIENVMANAGER_HPP

#include <jni.h>

#include "EyerCore/EyerCore.hpp"
#include "EyerJNIEnv.hpp"

namespace Eyer
{
    class EyerJNIEnvManager
    {
    public:
        static int Init(JavaVM * vm, JNIEnv * env, const EyerString & clazzLoaderName);

        static EyerJNIEnv AttachCurrentThread();
        static int DetachCurrentThread();

        static jclass FindClazz(EyerJNIEnv * env, const char * name);

    private:
        EyerJNIEnvManager();

        static JavaVM * vm;
        static jobject clazzLoaderObject;
        static jmethodID findClassMethod;
    };
}



#endif //EYERCAMERAANDROID_EYERJNIENVMANAGER_HPP
