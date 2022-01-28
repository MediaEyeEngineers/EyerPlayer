#ifndef EYERLIB_EYERGL_IOS_CONTEXT_C_INTERFACE_H
#define EYERLIB_EYERGL_IOS_CONTEXT_C_INTERFACE_H

/*
int         ios_gl_ctx_test_add         (int a, int b);

void *      ios_gl_ctx_init             (void * cLayer, int * screenFramebuffer);
int         ios_gl_ctx_uninit           (void * ctx);

int         ios_gl_ctx_swapbuffer       (void * ctx);


void *      ios_gl
*/

int         ios_gl_ctx_test_add         (int a, int b);

void *  ios_gl_ctx_init     ();
int     ios_gl_ctx_uninit   (void * gl_ctx);

int     ios_gl_ctx_create_surface    (void * gl_ctx, void * cLayer, unsigned int * _frameBuffer, unsigned int * _colorRenderBuffer);
int     ios_gl_ctx_destroy_surface   (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer);

int     ios_gl_ctx_makecurrent       (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer);
int     ios_gl_ctx_swapbuffers       (void * gl_ctx, unsigned int _frameBuffer, unsigned int _colorRenderBuffer);

#endif //EYERLIB_EYERGL_IOS_CONTEXT_C_INTERFACE_H
