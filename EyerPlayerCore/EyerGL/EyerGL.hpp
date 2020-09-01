#ifndef	EYER_LIB_GL_AV_H
#define	EYER_LIB_GL_AV_H

#include "EyerCore/EyerCore.hpp"
#include <vector>

#ifdef QT_EYER_PLAYER
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#else
#endif

namespace Eyer
{
    class EyerGLWindow;
    class EyerGLWindowPrivate;
    class EyerGLCMD;

    class EyerGLComponent;
    class EyerGLTextDraw;
    class EyerGLSingleTextureDraw;
    class EyerGLFrameDraw;

    class EyerGLShader;
    class EyerGLProgram;
    class EyerGLVAO;
    class EyerGLTexture;

    class _EyerGLContextFunc
    {
    };

#ifdef QT_EYER_PLAYER
#define EyerGLContextFunc QOpenGLFunctions_3_3_Core
#else
#define EyerGLContextFunc _EyerGLContextFunc
#endif

    class EyerGLCMD
    {
    public:
        virtual ~EyerGLCMD()
        {

        }
    };

    enum EyerGLShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    class EyerGLShader : public EyerGLCMD
    {
    private:
        EyerGLShaderType type = EyerGLShaderType::VERTEX_SHADER;
        EyerString src;
        unsigned int shaderId = 0;

        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLShader(EyerGLShaderType type, EyerString src, EyerGLContextFunc * _ctx = nullptr);
        ~EyerGLShader();

        int Compile();

        unsigned int GL_GetShaderId();
    };

    class EyerGLProgram : public EyerGLCMD
    {
    private:
        EyerString vertexShaderSrc;
        EyerString fragmentShaderSrc;

        unsigned int programId = 0;

        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLProgram(EyerString vertexShaderSrc, EyerString fragmentShaderSrc, EyerGLContextFunc * _ctx = nullptr);
        ~EyerGLProgram();
        int LinkProgram();
        int UseProgram();

        int PutUniform1i(EyerString key, int value);
        int PutMatrix4fv(EyerString key, EyerMat4x4 & mat);
        int PutUniform1f(EyerString key, float value);
    };

    class EyerGLVAO : public EyerGLCMD
    {
    private:
        unsigned int VAOId = 0;
        unsigned int EBOId = 0;
        std::vector<unsigned int> vboList;

        int DrawTime = 0;

        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLVAO(EyerGLContextFunc * ctx = nullptr);
        ~EyerGLVAO();

        int SetEBO(unsigned int * EBOdata, int bufferSize);
        int AddVBO(float * VBOdata, int bufferSize, int layout, int size = 3, unsigned int stride = 0);

        int DrawVAO();
    };

    class EyerGLDrawTexture
    {
    public:
        EyerString uniformName;
        EyerGLTexture * texture = nullptr;
    };

    class EyerGLDraw : public EyerGLCMD
    {
    private:
        EyerString vertexShaderSrc;
        EyerString fragmentShaderSrc;

        EyerGLProgram * program = nullptr;
        EyerGLVAO * vao = nullptr;

        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLDraw(EyerString vertexShaderSrc, EyerString fragmentShaderSrc, EyerGLContextFunc * ctx = nullptr);
        ~EyerGLDraw();

        int Init();

        int SetVAO(EyerGLVAO * vao);
        int PutTexture(EyerString uniform, EyerGLTexture * texture, int textureIndex = 0);
        int PutMatrix4fv(EyerString uniform, EyerMat4x4 & mat);
        int PutUniform1f(EyerString uniform, float val);
        int PutUniform1i(EyerString uniform, int val);

        int Draw();
    };

    class EyerGLTexture : public EyerGLCMD
    {
    private:
        unsigned int textureId = 0;
        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLTexture(EyerGLContextFunc * ctx = nullptr);
        ~EyerGLTexture();

        unsigned int GL_GetTextureId();

        int SetDataRedChannel(unsigned char * data,int width,int height);
        int SetDataRGChannel(unsigned char * data,int width,int height);
        int SetDataRGBAChannel(unsigned char * data,int width,int height);
    };

    class EyerGLFrameBuffer : public EyerGLCMD
    {
    private:
        EyerLinkedList<EyerGLDraw *> drawList;
        EyerLinkedList<EyerGLComponent *> componentList;

        unsigned int fbo = 0;

        int width = 0;
        int height = 0;

        EyerGLTexture * texture = nullptr;
        EyerGLContextFunc * ctx = nullptr;
    public:
        EyerGLFrameBuffer(int w, int h, EyerGLTexture * texture = nullptr, EyerGLContextFunc * ctx = nullptr);
        ~EyerGLFrameBuffer();

        int AddDraw(EyerGLDraw * draw);
        int AddComponent(EyerGLComponent * component);
        int ClearAllComponent();

        int Clear();
        int Clear(float r, float g, float b, float a);

        int Draw();

        int ReadPixel(int x, int y, int width, int height, unsigned char * data);
    };


    class EyerGLComponent
    {
    public:
        int width = 0;
        int height = 0;
    public:
        virtual ~EyerGLComponent();

        virtual int Draw() = 0;

        int Viewport(int w, int h);
    };

    class EyerGLRenderTask
    {
    public:
        EyerGLRenderTask();
        virtual ~EyerGLRenderTask();

        int SetWH(int w, int h);

        // 外部只能复写，不能调用
        virtual int Render() = 0;
        virtual int Init() = 0;
        virtual int Destory() = 0;

    public:
        int w = 0;
        int h = 0;
    };

    class EyerGLRenderTaskQueue
    {
    public:
        EyerGLRenderTaskQueue();
        ~EyerGLRenderTaskQueue();

        int GetSize();

        int PushRendTask(EyerGLRenderTask * renderTask);
        int PopAndRender(int w, int h);
        int PopAndRenderAndFree(int w, int h);

        int PopAndFree();
    private:
        EyerLockQueue<EyerGLRenderTask> taskQueue;
    };
}

#endif
