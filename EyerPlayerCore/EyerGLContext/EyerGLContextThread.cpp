#include "EyerGLContext.hpp"

namespace Eyer
{
    EyerGLContextThread::EyerGLContextThread(EyerGLContext * _glCtx)
    {
        glCtx = _glCtx;
    }

    EyerGLContextThread::~EyerGLContextThread()
    {

    }

    void EyerGLContextThread::Run()
    {
        EyerLog("EyerGLContextThread Start\n");

        glCtx->MakeCurrent();

        glClearColor(1.0, 1.0, 0.0, 1.0);
        while(!stopFlag){
            Eyer::EyerTime::EyerSleepMilliseconds(100);

            EyerLog("Clear\n");

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glFinish();

            glCtx->SwapBuffers();
            /*
            int queueSize = taskQueue.Size();
            while(queueSize > 0){
                EyerGLRenderTask * renderTask = nullptr;
                taskQueue.FrontPop(&renderTask);
                if(renderTask != nullptr){
                    renderTask->Init();

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    renderTask->Render();
                    glFinish();
                    eglSwapBuffers(mEglDisplay, window);

                    renderTask->Destory();

                    delete renderTask;
                }
                queueSize = taskQueue.Size();
            }
            */
        }

        EyerLog("EyerGLContextThread End\n");
    }

    int EyerGLContextThread::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }

    int EyerGLContextThread::AddRenderTask(EyerGLRenderTask * task)
    {
        taskQueue.Push(task);
        return 0;
    }

    int EyerGLContextThread::GetW()
    {
        return w;
    }

    int EyerGLContextThread::GetH()
    {
        return h;
    }
}