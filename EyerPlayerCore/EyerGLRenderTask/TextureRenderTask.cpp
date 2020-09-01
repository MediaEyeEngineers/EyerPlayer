#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include "TextureRenderTask.hpp"

#include "EyerGLShader/Shader.hpp"

namespace Eyer {
    TextureRenderTask::TextureRenderTask()
    {

    }

    TextureRenderTask::~TextureRenderTask()
    {

    }

    int TextureRenderTask::Render()
    {
        textureDraw->Draw();
        return 0;
    }

    int TextureRenderTask::Init()
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

        textureDraw = new Eyer::EyerGLDraw(Eyer::EYER_GL_SHADER::ExternalOES_TEXTURE_VERTEX_SHADER, Eyer::EYER_GL_SHADER::ExternalOES_TEXTURE_FRAGMENT_SHADER);
        textureDraw->Init();

        vao = new Eyer::EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        textureDraw->SetVAO(vao);

        return 0;
    }

    int TextureRenderTask::Destory()
    {
        if(textureDraw != nullptr){
            delete textureDraw;
            textureDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
        return 0;
    }

    int TextureRenderTask::SetTexId(int _texId)
    {
        texId = _texId;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_EXTERNAL_OES, texId);
        textureDraw->PutUniform1i("imageTex", 0);
        return 0;
    }
}