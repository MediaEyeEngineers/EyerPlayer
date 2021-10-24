#include "EyerGLTexture.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLTexture::EyerGLTexture(EyerGLTextureType textureType)
    {
        type = GL_TEXTURE_2D;
        if(textureType == EyerGLTextureType::EYER_GL_TEXTURE_2D){
            type = GL_TEXTURE_2D;
        }
#ifdef EYER_PLATFORM_ANDROID
        if(textureType == EyerGLTextureType::EYER_GL_TEXTURE_EXTERNAL_OES){
            type = GL_TEXTURE_EXTERNAL_OES;
        }
#endif
        glGenTextures(1, &textureId);

        glBindTexture(type, textureId);
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(type, 0);
    }

    EyerGLTexture::~EyerGLTexture()
    {
        if(textureId != 0){
            glDeleteTextures(1, &textureId);
            textureId = 0;
        }
    }

    int EyerGLTexture::SetDataREDChannel(unsigned char * data, int width, int height)
    {
        glBindTexture(type, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(type, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glBindTexture(type, 0);
        return 0;
    }

    int EyerGLTexture::SetDataLUMINANCEChannel(unsigned char * data, int width, int height)
    {
        glBindTexture(type, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
#ifdef EYER_PLATFORM_IOS
        glTexImage2D(type, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
#endif
        glBindTexture(type, 0);
        return 0;
    }

    int EyerGLTexture::SetDataRGBAChannel(unsigned char * data, int width, int height)
    {
        glBindTexture(type, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(type, 0);
        return 0;
    }

    int EyerGLTexture::SetDataBGRAChannel(unsigned char * data, int width, int height)
    {
#ifdef EYER_PLATFORM_ANDROID
        glBindTexture(type, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(type, 0);
#endif

#ifdef EYER_PLATFORM_IOS
        glBindTexture(type, textureId);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(type, 0, GL_BGRA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
        glBindTexture(type, 0);
#endif

        return 0;
    }
}