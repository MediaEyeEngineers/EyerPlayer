#ifndef EYERCAMERAANDROID_EYERJNIENV_HPP
#define EYERCAMERAANDROID_EYERJNIENV_HPP

#include <jni.h>

namespace Eyer
{
    class EyerJNIEnv
    {
    public:
        EyerJNIEnv(JNIEnv * _env);
        ~EyerJNIEnv();

        EyerJNIEnv(EyerJNIEnv && _env);

    public:
        JNIEnv * env = nullptr;

    private:
        EyerJNIEnv(const EyerJNIEnv & jniEnv) = delete;
        EyerJNIEnv & operator = (const EyerJNIEnv & jniEnv) = delete;
    };
}

#endif //EYERCAMERAANDROID_EYERJNIENV_HPP
