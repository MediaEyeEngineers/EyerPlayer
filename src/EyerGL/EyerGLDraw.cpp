#include "EyerGLDraw.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLDraw::EyerGLDraw(const EyerString & vertexShaderStr, const EyerString & fragmentShaderStr, OpenGLFunctionsContext * _funcCtx)
    {
        funcCtx = _funcCtx;

        vertextShader   = new EyerGLShader(EyerGLShaderType::VERTEX_SHADER,     vertexShaderStr, funcCtx);
        vertextShader->Compile();

        fragmentShader  = new EyerGLShader(EyerGLShaderType::FRAGMENT_SHADER,   fragmentShaderStr, funcCtx);
        fragmentShader->Compile();

        program = new EyerGLProgram(funcCtx);
        program->AttachShader(vertextShader);
        program->AttachShader(fragmentShader);
        program->LinkProgram();
    }

    EyerGLDraw::~EyerGLDraw()
    {
        if(program != nullptr){
            delete program;
            program = nullptr;
        }

        if(vertextShader != nullptr){
            delete vertextShader;
            vertextShader = nullptr;
        }

        if(fragmentShader != nullptr){
            delete fragmentShader;
            fragmentShader = nullptr;
        }
    }

    int EyerGLDraw::SetVAO(EyerGLVAO * _vao)
    {
        vao = _vao;
        return 0;
    }

    int EyerGLDraw::Draw(EyerGLDrawType drawType)
    {
        if(program != nullptr){
            program->UseProgram();
        }

        if(vao != nullptr){
            vao->DrawVAO(drawType);
        }

        glFinish();

        return 0;
    }

    int EyerGLDraw::PutUniform1i(const EyerString & key, int value)
    {
        program->UseProgram();
        return program->PutUniform1i(key, value);
    }

    int EyerGLDraw::PutUniform1f(const EyerString & key, float value)
    {
        program->UseProgram();
        return program->PutUniform1f(key, value);
    }

    int EyerGLDraw::PutMatrix4fv(const EyerString & key, const EatrixF4x4 & _mat)
    {
        program->UseProgram();
        return program->PutMatrix4fv(key, _mat);
    }

    int EyerGLDraw::PutMatrix3fv(const EyerString & key, const EatrixF3x3 & _mat)
    {
        program->UseProgram();
        return program->PutMatrix3fv(key, _mat);
    }

    int EyerGLDraw::PutTexture(const EyerString & uniform, EyerGLTexture * texture, int textureIndex)
    {
        program->UseProgram();

#ifdef EYER_PLATFORM_QT
        funcCtx->glActiveTexture(GL_TEXTURE0 + textureIndex);
        funcCtx->glBindTexture(texture->type, texture->textureId);
#else
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        glBindTexture(texture->type, texture->textureId);
#endif
        program->PutUniform1i(uniform.str, textureIndex);

        return 0;
    }
}