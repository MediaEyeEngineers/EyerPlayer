#ifndef	EYER_CODEC_H
#define	EYER_CODEC_H

namespace Eyer
{
    class EyerMediaCodec
    {
    public:
        EyerMediaCodec();
        ~EyerMediaCodec();

        int Init(int w, int h);
    };
}

#endif