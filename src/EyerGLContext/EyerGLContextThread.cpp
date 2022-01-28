#include "EyerGLContext.hpp"

#include "EyerGLContextThread.hpp"
#include "EyerGLContextThreadPrivate.hpp"

namespace Eyer
{
    EyerGLContextThread::EyerGLContextThread()
    {
        piml = new EyerGLContextThreadPrivate();
    }

    EyerGLContextThread::~EyerGLContextThread()
    {
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    void EyerGLContextThread::Run()
    {
        Init();
        Render();
        Uninit();
    }

    int EyerGLContextThread::Init()
    {
        return 0;
    }

    int EyerGLContextThread::Uninit()
    {
        return 0;
    }

    int EyerGLContextThread::SetWH(int w, int h)
    {
        piml->width = w;
        piml->height = h;
        return 0;
    }

    int EyerGLContextThread::GetW()
    {
        return piml->width;
    }

    int EyerGLContextThread::GetH()
    {
        return piml->height;
    }

    EyerGLSurface * EyerGLContextThread::CreateSurface   (EyerGLWindows windows)
    {
        return nullptr;
    }

    int EyerGLContextThread::MakeCurrent                 (EyerGLSurface * surface)
    {
        return 0;
    }

    int EyerGLContextThread::SwapBuffers                 (EyerGLSurface * surface)
    {
        return 0;
    }

    int EyerGLContextThread::DestroySurface              (EyerGLSurface * surface)
    {
        return 0;
    }
}