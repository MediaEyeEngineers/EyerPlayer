#include "EyerJNIEnv.hpp"

namespace Eyer
{
    EyerJNIEnv::EyerJNIEnv(JNIEnv * _env)
        : env(_env)
    {

    }

    EyerJNIEnv::EyerJNIEnv(EyerJNIEnv && _env)
    {
        env = _env.env;
        _env.env = nullptr;
    }

    EyerJNIEnv::~EyerJNIEnv()
    {

    }
}