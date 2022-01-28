#include "EyerGL_IOS_Context_C_Interface.h"
#include <stdio.h>

#import <GLKit/GLKit.h>

/*
int ios_gl_ctx_test_add(int a, int b)
{
    return a + b;
}

void *      ios_gl_ctx_init             (void * cLayer, int * screenFramebuffer)
{
    CAEAGLLayer * eaglLayer = (__bridge CAEAGLLayer *)cLayer;

    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    [EAGLContext setCurrentContext:context];

    GLuint colorRenderBuffer;
    glGenRenderbuffers(1, &colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
    
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer);
    
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];

    *screenFramebuffer = framebuffer;

    glClearColor(0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    [context presentRenderbuffer:GL_RENDERBUFFER];

    void * _ctx = (__bridge void *)context;

    return _ctx;
}

int         ios_gl_ctx_uninit           (void * _ctx)
{
    EAGLContext * context = (__bridge EAGLContext *)_ctx;
    return 0;
}

int         ios_gl_ctx_swapbuffer       (void * _ctx)
{
    EAGLContext * context = (__bridge EAGLContext *)_ctx;

    [context presentRenderbuffer:GL_RENDERBUFFER];

    return 0;
}
*/

int ios_gl_ctx_test_add(int a, int b)
{
    return a + b;
}

void * ios_gl_ctx_init()
{
    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    [EAGLContext setCurrentContext:context];

    return (__bridge void *)context;
}

int     ios_gl_ctx_uninit   (void * gl_ctx)
{
    EAGLContext * context = (__bridge EAGLContext *)gl_ctx;
    return 0;
}

int     ios_gl_ctx_create_surface   (void * gl_ctx, void * cLayer, unsigned int * _frameBuffer, unsigned int * _colorRenderBuffer)
{
    EAGLContext * context = (__bridge EAGLContext *)gl_ctx;
    CAEAGLLayer * eaglLayer = (__bridge CAEAGLLayer *)cLayer;

    [EAGLContext setCurrentContext:context];

    GLuint colorRenderBuffer;
    glGenRenderbuffers(1, &colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
    
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer);

    *_frameBuffer = framebuffer;
    *_colorRenderBuffer = colorRenderBuffer;

    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];

    return 0;
}

int     ios_gl_ctx_destroy_surface   (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer)
{
    EAGLContext * context = (__bridge EAGLContext *)gl_ctx;

    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

    return 0;
}

int     ios_gl_ctx_makecurrent      (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer)
{
    EAGLContext * context = (__bridge EAGLContext *)gl_ctx;

    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

    [EAGLContext setCurrentContext:context];
    return 0;
}

int     ios_gl_ctx_swapbuffers      (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer)
{
    EAGLContext * context = (__bridge EAGLContext *)gl_ctx;

    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);


    [context presentRenderbuffer:GL_RENDERBUFFER];
    return 0;
}