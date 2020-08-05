#include "EyerGL.hpp"

namespace Eyer
{
    EyerGLRenderTaskQueue::EyerGLRenderTaskQueue()
    {

    }

    EyerGLRenderTaskQueue::~EyerGLRenderTaskQueue()
    {
        
    }

    int EyerGLRenderTaskQueue::PushRendTask(EyerGLRenderTask * renderTask)
    {
        taskQueue.Push(renderTask);
        return 0;
    }

    int EyerGLRenderTaskQueue::PopAndRender(int w, int h)
    {
        EyerGLRenderTask * task = nullptr;
        taskQueue.FrontPop(&task);
        if(task != nullptr){
            task->Init();
            task->SetWH(w, h);
            task->Render();
        }

        return 0;
    }

    int EyerGLRenderTaskQueue::PopAndRenderAndFree(int w, int h)
    {
        EyerGLRenderTask * task = nullptr;
        taskQueue.FrontPop(&task);
        if(task != nullptr){
            task->Init();
            task->SetWH(w, h);
            task->Render();

            task->Destory();

            delete task;
        }

        return 0;
    }

    int EyerGLRenderTaskQueue::PopAndFree()
    {
        EyerGLRenderTask * task = nullptr;
        taskQueue.FrontPop(&task);
        if(task != nullptr){
            delete task;
        }

        return 0;
    }

    int EyerGLRenderTaskQueue::GetSize()
    {
        return taskQueue.Size();
    }
}