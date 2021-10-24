#include "EyerTextureCache.hpp"

namespace Eyer
{
    EyerTextureCache::EyerTextureCache()
    {

    }

    EyerTextureCache::~EyerTextureCache()
    {

    }

    int EyerTextureCache::Put(const EyerString & key, EyerGLTexture * texture)
    {
        textureCache.insert(std::pair<EyerString, EyerGLTexture *>(key, texture));
        return 0;
    }

    EyerGLTexture * EyerTextureCache::Get(const EyerString & key)
    {
        std::map<EyerString, EyerGLTexture *>::iterator it = textureCache.find(key);
        if (it != textureCache.end()){
            return it->second;
        }
        return nullptr;
    }
}