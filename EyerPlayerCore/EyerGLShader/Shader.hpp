#ifndef	EYER_LIB_GL_SHADER_TEMP_SHOW_H
#define	EYER_LIB_GL_SHADER_TEMP_SHOW_H

#include "ShaderH.hpp"

namespace Eyer {

    class EYER_GL_SHADER {
    public:
        static char * YUV_2_TEXTURE_VERTEX_SHADER;
        static char * YUV_2_TEXTURE_FRAGMENT_SHADER;

        static char * ExternalOES_TEXTURE_VERTEX_SHADER;
        static char * ExternalOES_TEXTURE_FRAGMENT_SHADER;
    };
}

#endif
