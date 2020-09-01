#include "EyerGLContext.hpp"

namespace Eyer
{
    EyerGLContextThread::EyerGLContextThread()
    {
    }

    EyerGLContextThread::~EyerGLContextThread()
    {

    }

    void EyerGLContextThread::Run()
    {
        EyerLog("EyerGLContextThread Start\n");

        int width = 1920;
        int height = 1080;
        Eyer::EyerString title = "EyerWand GLContext";

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title.str, NULL, NULL);
        if (window == NULL) {
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        }

        glClearColor(1.0, 1.0, 1.0, 1.0);
        while(!stopFlag){
            // Eyer::EyerTime::EyerSleepMilliseconds(1);

            int queueSize = taskQueue.Size();
            while(queueSize > 0){
                EyerGLRenderTask * renderTask = nullptr;
                taskQueue.FrontPop(&renderTask);
                if(renderTask != nullptr){
                    renderTask->Init();

                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    renderTask->Render();
                    glFinish();

                    glfwSwapBuffers(window);
                    glfwPollEvents();

                    renderTask->Destory();

                    delete renderTask;
                }
                queueSize = taskQueue.Size();
            }
            if(queueSize <= 0){
                /*
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glfwSwapBuffers(window);
                glfwPollEvents();
                */
            }
        }

        glfwDestroyWindow(window);
        window = NULL;

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