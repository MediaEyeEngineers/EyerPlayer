#include "EyerGLTestComponent.hpp"

#include "EyerGL/GLHeader.hpp"

namespace Eyer
{
    EyerGLTestComponent::EyerGLTestComponent()
    {
        float vertex[] = {
                1.0, 1.0, 0.0,
                1.0, -1.0, 0.0,
                -1.0, -1.0, 0.0,
                -1.0, 1.0, 0.0
        };
        float coor[] = {
                1.0, 1.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0
        };
        unsigned int vertexIndex[] = {
                0, 1, 2,
                0, 2, 3
        };

        const char * VERTEX_SHADER = (char *)EYER_GL_SHADER(
            \#version 300 es\n
            precision highp float;\n
            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec3 coor;

            uniform float iTime;

            out vec2 outCoor;

            void main(){
                outCoor = vec2(coor.x, coor.y);
                gl_Position = vec4(pos * iTime, 1.0);
            }
        );

        const char * FRAGMENT_SHADER = (char *)EYER_GL_SHADER(
            \#version 300 es\n
            precision highp float;\n

            out vec4 color;
            in vec2 outCoor;

            void main()
            {
                color = vec4(outCoor, 1.0, 1.0);
            }
        );

        draw = new EyerGLDraw(VERTEX_SHADER, FRAGMENT_SHADER);

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        draw->SetVAO(vao);   
    }

    EyerGLTestComponent::~EyerGLTestComponent()
    {
        if(draw != nullptr){
            delete draw;
            draw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
    }

    int EyerGLTestComponent::Draw()
    {
        // EyerLog("w: %d, h: %d\n", width, height);
        draw->PutUniform1f("width", width);
        draw->PutUniform1f("height", height);
        draw->PutUniform1f("iTime", sinf(iTime * 0.01));

        draw->Draw();

        return 0;
    }

    int EyerGLTestComponent::SetTime(int _iTime)
    {
        iTime = _iTime;
        return 0;
    }

    int EyerGLTestComponent::SetWH(int w, int h)
    {
        width = w;
        height = h;
        return 0;
    }
}