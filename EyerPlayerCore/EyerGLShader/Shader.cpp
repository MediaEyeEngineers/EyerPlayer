#include "Shader.hpp"

namespace Eyer
{
    char * EYER_GL_SHADER::YUV_2_TEXTURE_VERTEX_SHADER = (char *)SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;

        void main()
        {
            outCoor = coor;
            gl_Position = vec4(pos, 1.0);
        }
    );

    char * EYER_GL_SHADER::YUV_2_TEXTURE_FRAGMENT_SHADER = (char *)SHADER(
        precision mediump float;
        out vec4 color;

        uniform sampler2D y;
        uniform sampler2D u;
        uniform sampler2D v;

        uniform int colorRange;

        in vec3 outCoor;

        void main(){
            vec2 t = vec2(outCoor.x, outCoor.y);
            t.y = 1.0 - t.y;

            vec3 yuv;
            vec3 rgb;

            yuv.x = texture(y, t).r;
            yuv.y = texture(u, t).r - 0.5;
            yuv.z = texture(v, t).r - 0.5;

            rgb = mat3( 1, 1, 1,
                        0, -0.3437, 1.7722,
                        1.4017, -0.7142, 0) * yuv;

            color = vec4(rgb, 1.0);
        }
    );


    char * EYER_GL_SHADER::ExternalOES_TEXTURE_VERTEX_SHADER = (char *)SHADER(
         layout (location = 0) in vec3 pos;
         layout (location = 1) in vec3 coor;

         out vec3 outCoor;

         void main(){
             outCoor = coor;
             gl_Position = vec4(pos * 1.0, 1.0);
         }
    );

    char * EYER_GL_SHADER::ExternalOES_TEXTURE_FRAGMENT_SHADER = (char *)SHADER(
          \#extension GL_OES_EGL_image_external_essl3 : require\n

          precision highp float;
          out vec4 color;
          in vec3 outCoor;

          uniform samplerExternalOES imageTex;

          void main()
          {
              vec2 TexCoords = vec2(outCoor.x, 1.0 - outCoor.y);
              color = texture(imageTex, TexCoords);
          }
    );
}