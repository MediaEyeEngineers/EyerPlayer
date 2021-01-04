#ifndef EYE_LIB_EYERHTTPPOOL_PRIVATE_HPP
#define EYE_LIB_EYERHTTPPOOL_PRIVATE_HPP

#include <curl/curl.h>

namespace Eyer{
    class EyerHttpPoolPrivate
    {
    public:
        CURLM * multi_handle = nullptr;
        int still_running = 0;
    };
}

#endif