#ifndef	EYER_LIB_GL_SHADER_HEADER_H
#define	EYER_LIB_GL_SHADER_HEADER_H

#define	STRINGIZE(x)	#x

#ifdef EYER_PLATFORM_ANDROID
#define	SHADER(shader) "#version 300 es\n" STRINGIZE(shader)
#else
#define	SHADER(shader) "#version 330\n" STRINGIZE(shader)
#endif


#endif