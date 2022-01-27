#ifndef EYERPLAYERANDROID_EYERJNIBYTEARRAY_HPP
#define EYERPLAYERANDROID_EYERJNIBYTEARRAY_HPP

#include <jni.h>
#include "EyerJNIEnv.hpp"

namespace Eyer
{
    class EyerJNIByteArray
    {
    public:
        EyerJNIByteArray(EyerJNIEnv * _env, int _len);
        ~EyerJNIByteArray();

        int SetData(uint8_t * data);

        jbyteArray GetJObject();
    public:
        EyerJNIEnv * env = nullptr;
        jbyteArray array = nullptr;
        int len = 0;
    };
}

#endif //EYERPLAYERANDROID_EYERJNIBYTEARRAY_HPP
