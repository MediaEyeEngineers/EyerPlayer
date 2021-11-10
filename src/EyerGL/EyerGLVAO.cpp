#include "EyerGLVAO.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLVAO::EyerGLVAO(OpenGLFunctionsContext * _funcCtx)
    {
        funcCtx = _funcCtx;

#ifdef EYER_PLATFORM_QT
        funcCtx->glGenVertexArrays(1, &VAOId);
#else
        glGenVertexArrays(1, &VAOId);
#endif
        
    }

    EyerGLVAO::~EyerGLVAO()
    {
        for(int i=0;i<vboList.size();i++){
            unsigned int vbo = vboList[i];
#ifdef EYER_PLATFORM_QT
            funcCtx->glDeleteBuffers(1, &vbo);
#else
            glDeleteBuffers(1, &vbo);
#endif
            
        }
        vboList.clear();

        if(EBOId != 0){
#ifdef EYER_PLATFORM_QT
            funcCtx->glDeleteBuffers(1, &EBOId);
#else
            glDeleteBuffers(1, &EBOId);
#endif
            
            EBOId = 0;
        }

        if(VAOId != 0){
#ifdef EYER_PLATFORM_QT
            funcCtx->glDeleteVertexArrays(1, &VAOId);
#else
            glDeleteVertexArrays(1, &VAOId);
#endif
            
            VAOId = 0;
        }
    }

    int EyerGLVAO::AddVBO(float * VBOdata, int bufferSize, int layout, int size, unsigned int stride)
    {
#ifdef EYER_PLATFORM_QT
        funcCtx->glBindVertexArray(VAOId);

        GLuint VBO;
        funcCtx->glGenBuffers(1,&VBO);

        vboList.push_back(VBO);

        funcCtx->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        funcCtx->glBufferData(GL_ARRAY_BUFFER, bufferSize, VBOdata, GL_STATIC_DRAW);

        funcCtx->glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
        funcCtx->glEnableVertexAttribArray(layout);

        funcCtx->glBindVertexArray(0);
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

    int EyerGLVAO::SetEBO(unsigned int * EBOdata, int bufferSize)
    {
        drawTime = bufferSize / (sizeof(int));

#ifdef EYER_PLATFORM_QT
        funcCtx->glBindVertexArray(VAOId);

        funcCtx->glGenBuffers(1,&EBOId);
        funcCtx->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
        funcCtx->glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, EBOdata, GL_STATIC_DRAW);

        funcCtx->glBindVertexArray(0);
#else
        glBindVertexArray(VAOId);

        glGenBuffers(1,&EBOId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, EBOdata, GL_STATIC_DRAW);

        glBindVertexArray(0);
#endif

        return 0;
    }

    int EyerGLVAO::DrawVAO(EyerGLDrawType drawType)
    {
#ifdef EYER_PLATFORM_QT
        funcCtx->glBindVertexArray(VAOId);
        if(drawType == EyerGLDrawType::TRIANGLES){
            funcCtx->glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::LINE_LOOP){
            funcCtx->glDrawElements(GL_LINE_LOOP, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::LINE){
            // glDrawElements(GL_LINE, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::POINT){
            // glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);
            funcCtx->glDrawElements(GL_POINTS, drawTime, GL_UNSIGNED_INT, 0);
        }
        funcCtx->glBindVertexArray(0);
#else
        glBindVertexArray(VAOId);
        if(drawType == EyerGLDrawType::TRIANGLES){
            glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::LINE_LOOP){
            glDrawElements(GL_LINE_LOOP, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::LINE){
            // glDrawElements(GL_LINE, drawTime, GL_UNSIGNED_INT, 0);
        }
        else if(drawType == EyerGLDrawType::POINT){
            // glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);
            glDrawElements(GL_POINTS, drawTime, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
#endif

        return 0;
    }
}