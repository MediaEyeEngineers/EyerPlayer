#ifndef EYERCAMERAANDROID_EYERTEXTURECACHE_HPP
#define EYERCAMERAANDROID_EYERTEXTURECACHE_HPP

#include "EyerGLTexture.hpp"
#include "EyerCore/EyerCore.hpp"
#include <map>

namespace Eyer
{
    class EyerTextureCache
    {
    public:
        EyerTextureCache();
        ~EyerTextureCache();

        int Put(const EyerString & key, EyerGLTexture * texture);
        EyerGLTexture * Get(const EyerString & key);

    private:
        std::map<EyerString, EyerGLTexture *> textureCache;
    };
}

#endif //EYERCAMERAANDROID_EYERTEXTURECACHE_HPP
