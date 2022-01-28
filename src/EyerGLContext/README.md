# EyerGLContext

EyerGLContext 封装了 *OpenGL Context* 和 *渲染线程* 的细节。

目前适配了 *Android* 和 *iOS* 两个操作系统，你可以使用相似的调用流程去进行调用。而不必理会其中细节。

## 接口调用

本模块的调用将围绕 EyerGLContextThread 这一个类来进行。

EyerGLContextThread 是一个线程，里面封装了 OpenGL 的线程相关的所有东西。

- GL Context

通常情况下，你可以写一个类继承自 EyerGLContextThread。EyerGLContextThread 中有一个纯虚函数 virtual int Render() = 0;，你要实现这个函数，并且在实现中完成你的渲染操作。

````c++

class MyRenderThread : public EyerGLContextThread
{
public:
    virtual int Render()
    {
        while(!stopFlag) // 这个 while 循环必须这样写，否则退出的时候有问题。
        {
                    
        }
        return 0;
    }
};

````

EyerGLContextThread 是一个线程，这个 virtual int Render() 函数将被运行到自线程里面去。

在 Render 运行之前，EyerGLContextThread 会为你创建一个 GLContext。在 Render 运行之后，EyerGLContextThread 会为你删除 Gl Context。

你只需要写渲染部分就可以了。

- EyerGLSurface

EyerGLSurface 表示的是一个 GL 的平面。通常情况下，如果你需要将渲染结果显示到屏幕上面，你就需要用到这个东西。（在 Android 上，MediaCodec 也会用到）

所以这里，在进入 Render 之后，往往第一步就是创建一个 EyerGLSurface，而在渲染退出后，要把这个 surface 销毁掉。

````c++

class MyRenderThread : public EyerGLContextThread
{
public:
    virtual int Render()
    {
        SvGLWindows windows = ...;//
        EyerGLSurface * surface = CreateSurface(windows);
        while(!stopFlag) // 这个 while 循环必须这样写，否则退出的时候有问题。
        {
    
        }
        if(surface != nullptr){
            DestroySurface(surface);
            surface = nullptr;
        }
        
        return 0;
    }
};

````

可以看到，CreateSurface 成员函数需要一个 SvGLWindows 对象，这个对象在 Android 上是一个 ANativeWindow *，在 iOS 上是一个 void * 指针，上层把 UIView 的 CALayer 传递下来强转成一个 void * 就可以了。

在每一帧开始前，要先选择的 Surface MakeCurrent 一下，渲染完毕后，要 SwapBuffers 一下。

````c++

class MyRenderThread : public EyerGLContextThread
{
public:
    virtual int Render()
    {
        SvGLWindows windows = ...;//
        EyerGLSurface * surface = CreateSurface(windows);
        while(!stopFlag) // 这个 while 循环必须这样写，否则退出的时候有问题。
        {
            MakeCurrent(surface);
            SwapBuffers(surface);
        }

        if(surface != nullptr){
            DestroySurface(surface);
            surface = nullptr;
        }
        
        return 0;
    }
};

````