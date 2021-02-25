#include "EyerGL.hpp"

#include "GLHeader.h"

namespace Eyer
{
    EyerGLVAO::EyerGLVAO(EyerGLContextFunc * _ctx)
    {
        ctx = _ctx;

#ifdef QT_EYER_PLAYER
        ctx->glGenVertexArrays(1, &VAOId);
#else
        glGenVertexArrays(1, &VAOId);
#endif

    }

    EyerGLVAO::~EyerGLVAO()
    {
        for(int i=0;i<vboList.size();i++){
            unsigned int vbo = vboList[i];
#ifdef QT_EYER_PLAYER
            ctx->glDeleteBuffers(1, &vbo);
#else
            glDeleteBuffers(1, &vbo);
#endif

        }
        vboList.clear();

        if(VAOId != 0){
#ifdef QT_EYER_PLAYER
            ctx->glDeleteVertexArrays(1, &VAOId);
#else
            glDeleteVertexArrays(1, &VAOId);
#endif
            VAOId = 0;
        }
    }

    int EyerGLVAO::DrawVAO()
    {
        if(VAOId == 0){
            return -1;
        }

#ifdef QT_EYER_PLAYER
        ctx->glBindVertexArray(VAOId);
        ctx->glDrawElements(GL_TRIANGLES, DrawTime, GL_UNSIGNED_INT, 0);
        ctx->glBindVertexArray(0);
#else
        glBindVertexArray(VAOId);
        glDrawElements(GL_TRIANGLES, DrawTime, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
#endif


        return 0;
    }

    int EyerGLVAO::SetEBO(unsigned int * EBOdata, int bufferSize)
    {
        if(VAOId == 0){
            return -1;
        }

        DrawTime = bufferSize / (sizeof(int));

#ifdef QT_EYER_PLAYER
        ctx->glBindVertexArray(VAOId);

        ctx->glGenBuffers(1,&EBOId);
        ctx->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
        ctx->glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, EBOdata, GL_STATIC_DRAW);

        ctx->glBindVertexArray(0);
#else
        glBindVertexArray(VAOId);

        glGenBuffers(1,&EBOId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, EBOdata, GL_STATIC_DRAW);

        glBindVertexArray(0);
#endif

        return 0;
    }

    int EyerGLVAO::AddVBO(float * VBOdata, int bufferSize, int layout, int size, unsigned int stride)
    {
#ifdef QT_EYER_PLAYER
        ctx->glBindVertexArray(VAOId);

        GLuint VBO;
        ctx->glGenBuffers(1,&VBO);

        vboList.push_back(VBO);

        ctx->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        ctx->glBufferData(GL_ARRAY_BUFFER, bufferSize, VBOdata, GL_STATIC_DRAW);

        ctx->glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
        ctx->glEnableVertexAttribArray(layout);

        ctx->glBindVertexArray(0);
#else
        glBindVertexArray(VAOId);

        GLuint VBO;
        glGenBuffers(1,&VBO);

        vboList.push_back(VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, VBOdata, GL_STATIC_DRAW);

        glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
        glEnableVertexAttribArray(layout);

        glBindVertexArray(0);
#endif

        return 0;
    }
}