#ifndef EYERLIB_EYERGLTEXTURE_HPP
#define EYERLIB_EYERGLTEXTURE_HPP

#include "GLHeader.hpp"
#include "EyerGLTextureType.hpp"

namespace Eyer
{
    class EyerGLTexture
    {
    public:
        EyerGLTexture(EyerGLTextureType textureType = EyerGLTextureType::EYER_GL_TEXTURE_2D);
        ~EyerGLTexture();

        int SetDataREDChannel(unsigned char * data, int width, int height);
        int SetDataLUMINANCEChannel(unsigned char * data, int width, int height);
        int SetDataRGBAChannel(unsigned char * data, int width, int height);
        int SetDataBGRAChannel(unsigned char * data, int width, int height);

    public:
        unsigned int textureId = 0;
        int type = -1;

    private:
        EyerGLTexture(const EyerGLTexture & texture) = delete;
        const EyerGLTexture & operator = (const EyerGLTexture & texture) = delete;
    };
}

#endif //EYERLIB_EYERGLTEXTURE_HPP
