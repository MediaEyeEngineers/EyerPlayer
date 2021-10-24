#include "EyerGLVAO.hpp"

#include "GLHeader.hpp"

namespace Eyer
{
    EyerGLVAO::EyerGLVAO()
    {
        glGenVertexArrays(1, &VAOId);
    }

    EyerGLVAO::~EyerGLVAO()
    {
        for(int i=0;i<vboList.size();i++){
            unsigned int vbo = vboList[i];
            glDeleteBuffers(1, &vbo);
        }
        vboList.clear();

        if(EBOId != 0){
            glDeleteBuffers(1, &EBOId);
            EBOId = 0;
        }

        if(VAOId != 0){
            glDeleteVertexArrays(1, &VAOId);
            VAOId = 0;
        }
    }

    int EyerGLVAO::AddVBO(float * VBOdata, int bufferSize, int layout, int size, unsigned int stride)
    {
        glBindVertexArray(VAOId);

        GLuint VBO;
        glGenBuffers(1,&VBO);

        vboList.push_back(VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, VBOdata, GL_STATIC_DRAW);

        glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
        glEnableVertexAttribArray(layout);

        glBindVertexArray(0);

        return 0;
    }

    int EyerGLVAO::SetEBO(unsigned int * EBOdata, int bufferSize)
    {
        drawTime = bufferSize / (sizeof(int));

        glBindVertexArray(VAOId);

        glGenBuffers(1,&EBOId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, EBOdata, GL_STATIC_DRAW);

        glBindVertexArray(0);

        return 0;
    }

    int EyerGLVAO::DrawVAO(EyerGLDrawType drawType)
    {
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

        return 0;
    }
}