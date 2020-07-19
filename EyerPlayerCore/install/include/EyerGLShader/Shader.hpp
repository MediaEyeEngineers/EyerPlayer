#ifndef	EYER_LIB_GL_SHADER_TEMP_SHOW_H
#define	EYER_LIB_GL_SHADER_TEMP_SHOW_H

#include "ShaderH.hpp"

namespace Eyer {

    class GL_SHADER {
    public:
        static char * TEST_VERTEX_SHADER;
        static char * TEST_FRAGMENT_SHADER;

        static char * YUV_VIDEO_VERTEX_SHADER;
        static char * YUV_VIDEO_FRAGMENT_SHADER;

        static char * TEXT_VERTEX_SHADER;
        static char * TEXT_FRAGMENT_SHADER;

        static char * POINT_VERTEX_SHADER;
        static char * POINT_FRAGMENT_SHADER;

        static char * SINGLE_TEXTURE_VERTEX_SHADER;
        static char * SINGLE_TEXTURE_FRAGMENT_SHADER;

        static char * FRAME_VERTEX_SHADER;
        static char * FRAME_FRAGMENT_SHADER;


        static char * YUV_2_TEXTURE_VERTEX_SHADER;
        static char * YUV_2_TEXTURE_FRAGMENT_SHADER;

        static char * MVP_TEXTURE_VERTEX_SHADER;
        static char * MVP_TEXTURE_FRAGMENT_SHADER;
    };
}

#endif
