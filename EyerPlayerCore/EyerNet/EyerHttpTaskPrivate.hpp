#ifndef	EYER_LIB_NET_HTTP_TASK_PRIVATE_H
#define	EYER_LIB_NET_HTTP_TASK_PRIVATE_H

#include <curl/curl.h>

namespace Eyer
{
    class EyerHttpTaskPrivate
    {
    public:
        CURL * hnd = nullptr;
    };
}

#endif