#ifndef	EYER_LIB_NET_SIMPLEST_HTTP_H
#define	EYER_LIB_NET_SIMPLEST_HTTP_H

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerSimplestHttp
    {
    public:
        EyerSimplestHttp();
        ~EyerSimplestHttp();

        int Get(Eyer::EyerBuffer & buffer, EyerString url);

        int SetDate(unsigned char * data, int dataLen);
    private:
        static size_t write_data(void * buffer, size_t size, size_t nmemb, void * userp);

        Eyer::EyerBuffer buffer;
    };
}

#endif