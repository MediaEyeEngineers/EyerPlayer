#ifndef	EYER_LIB_NET_HTTP_TASK_H
#define	EYER_LIB_NET_HTTP_TASK_H

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerHttpTaskPrivate;

    class EyerHttpTask
    {
    public:
        EyerHttpTask();
        ~EyerHttpTask();

        int SetUrl(EyerString & url);
        int SetDate(unsigned char * data, int dataLen);
        int GetBuffer(Eyer::EyerBuffer & buffer);

    public:
        static size_t write_data(void * buffer, size_t size, size_t nmemb, void * userp);

        EyerHttpTaskPrivate * piml = nullptr;
        Eyer::EyerBuffer buffer;
    };
}

#endif