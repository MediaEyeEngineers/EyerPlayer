#include "EyerGL.hpp"

#include "GLHeader.h"

namespace Eyer
{
    EyerGLDraw::EyerGLDraw(EyerString _vertexShaderSrc, EyerString _fragmentShaderSrc, EyerGLContext * _ctx)
    {
        ctx = _ctx;

        vertexShaderSrc = _vertexShaderSrc;
        fragmentShaderSrc = _fragmentShaderSrc;

        program = new EyerGLProgram(vertexShaderSrc, fragmentShaderSrc, ctx);
    }

    EyerGLDraw::~EyerGLDraw()
    {
        if(program != nullptr){
            delete program;
            program = nullptr;
        }
    }

    int EyerGLDraw::Init()
    {
        if(program == nullptr){
            return -1;
        }

        program->LinkProgram();

        return 0;
    }

    int EyerGLDraw::PutTexture(EyerString uniform, EyerGLTexture * texture, int textureIndex)
    {
        program->UseProgram();

#ifdef QT_EYER_PLAYER
        ctx->glActiveTexture(GL_TEXTURE0 + textureIndex);
        ctx->glBindTexture(GL_TEXTURE_2D, texture->GL_GetTextureId());
#else
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(GL_TEXTURE_2D, texture->GL_GetTextureId());
#endif
        program->PutUniform1i(uniform.str, textureIndex);

        return 0;
    }

    int EyerGLDraw::PutMatrix4fv(EyerString uniform, EyerMat4x4 & mat)
    {
        program->UseProgram();
        program->PutMatrix4fv(uniform, mat);
        return 0;
    }

    int EyerGLDraw::PutUniform1f(EyerString uniform, float val)
    {
        program->UseProgram();
        program->PutUniform1f(uniform, val);
        return 0;
    }

    int EyerGLDraw::PutUniform1i(EyerString uniform, int val)
    {
        program->UseProgram();
        program->PutUniform1i(uniform, val);
        return 0;
    }

    int EyerGLDraw::SetVAO(EyerGLVAO * _vao)
    {
        vao = _vao;
        return 0;
    }

    int EyerGLDraw::Draw()
    {
        if(program == nullptr){
            return -1;
        }

        if(vao == nullptr){
            return -2;
        }

        program->UseProgram();

        vao->DrawVAO();

#ifdef QT_EYER_PLAYER
        ctx->glFinish();
#else
        glFinish();
#endif

        return 0;
    }
}