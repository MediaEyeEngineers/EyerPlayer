#include "EyerPlayerVideoRender.h"

#include "EyerGLShader/ShaderH.hpp"
#include <QDebug>

#undef main
#define SHADER_MAIN_FUN main

namespace EyerPlayer {

    EyerPlayerVideoRender::EyerPlayerVideoRender(EyerGLContext * _ctx)
    {

        ctx = _ctx;

        float vertex[] = {
                1.0, 1.0, 0.0,
                1.0, -1.0, 0.0,
                -1.0, -1.0, 0.0,
                -1.0, 1.0, 0.0
        };
        float coor[] = {
                1.0, 1.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0
        };
        unsigned int vertexIndex[] = {
                0, 1, 2,
                0, 2, 3
        };

        char * vShader = (char *)SHADER(
            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec3 coor;

            out vec3 outCoor;

            uniform mat4 mvp;

            void SHADER_MAIN_FUN(){
                outCoor = coor;
                gl_Position = mvp * vec4(pos * 1.0, 1.0);
            }
        );
        char * fShader = (char *)SHADER(
            out vec4 color;

            uniform sampler2D y;
            uniform sampler2D u;
            uniform sampler2D v;
            uniform sampler2D uv;

            uniform int pix_fmt;

            in vec3 outCoor;
            void SHADER_MAIN_FUN(){
                vec2 t = vec2(outCoor.x, 1.0 - outCoor.y);

                vec3 yuv;
                vec3 rgb;

                mat3 kBt709VideoRangeYUV2RGBMatrix = mat3(  1.164, 1.164, 1.164,
                                                            0.0, -0.213, 2.112,
                                                            1.793, -0.533, 0.0);

                mat3 kBt709FullRangeYUV2RGBMatrix  = mat3(  1.164,  1.164,  1.164,
                                                            0.0,   -0.213,  2.112,
                                                            1.793, -0.533,  0.0);

                mat3 kBt601VideoRangeYUV2RGBMatrix = mat3(  1.164, 1.164, 1.164,
                                                            0.0, -0.392, 2.017,
                                                            1.596, -0.813, 0.0);

                mat3 kBt601FullRangeYUV2RGBMatrix = mat3(   1.0, 1.0, 1.0,
                                                            0.0, -0.343, 1.765,
                                                            1.4, -0.711, 0.0);

                if(101 == pix_fmt){
                    yuv.x = texture(y, t).r;
                    yuv.y = texture(u, t).r - 0.5;
                    yuv.z = texture(v, t).r - 0.5;
                }
                else if(105 == pix_fmt){
                    yuv.x = texture(y, t).r;
                    yuv.y = texture(uv, t).r - 0.5;
                    yuv.z = texture(uv, t).g - 0.5;
                }

                rgb = kBt709VideoRangeYUV2RGBMatrix * yuv;

                color = vec4(rgb, 1.0);

                float gamma = 1.2;
                color.rgb = pow(color.rgb, vec3(gamma));
            }
        );

        frameDraw = new Eyer::EyerGLDraw(vShader, fShader, ctx);
        frameDraw->Init();

        vao = new Eyer::EyerGLVAO(ctx);
        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        frameDraw->SetVAO(vao);


        yT      = new Eyer::EyerGLTexture(ctx);
        uT      = new Eyer::EyerGLTexture(ctx);
        vT      = new Eyer::EyerGLTexture(ctx);
        uvT     = new Eyer::EyerGLTexture(ctx);
    }

    EyerPlayerVideoRender::~EyerPlayerVideoRender()
    {
        if(frameDraw != nullptr){
            delete frameDraw;
            frameDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
        if(yT != nullptr){
            delete yT;
            yT = nullptr;
        }
        if(uT != nullptr){
            delete uT;
            uT = nullptr;
        }
        if(vT != nullptr){
            delete vT;
            vT = nullptr;
        }
        if(uvT != nullptr){
            delete uvT;
            uvT = nullptr;
        }
    }

    int EyerPlayerVideoRender::SetFrame(Eyer::EyerAVFrame * f)
    {
        frame = f;
        return 0;
    }

    int EyerPlayerVideoRender::SetMVP(Eyer::EyerMat4x4 & _mvp)
    {
        mvp = _mvp;
        return 0;
    }

    int EyerPlayerVideoRender::Draw()
    {
        if(frame != nullptr){
            int w = frame->GetWidth();
            int h = frame->GetHeight();

            if(frame->GetPixFormat() == Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUV420P){
                unsigned char * y = (unsigned char *)malloc(w * h);
                unsigned char * u = (unsigned char *)malloc(w * h);
                unsigned char * v = (unsigned char *)malloc(w * h);
                memset(y, 0, w * h);
                memset(u, 0, w * h);
                memset(v, 0, w * h);

                frame->GetYData(y);
                frame->GetUData(u);
                frame->GetVData(v);

                yT->SetDataRedChannel(y, w, h);
                uT->SetDataRedChannel(u, w / 2, h / 2);
                vT->SetDataRedChannel(v, w / 2, h / 2);

                free(y);
                free(u);
                free(v);


            }
            if(frame->GetPixFormat() == Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV12){
                unsigned char * y  = (unsigned char *)malloc(w * h);
                unsigned char * uv = (unsigned char *)malloc(w * h);
                memset(y,   0, w * h);
                memset(uv,  0, w * h);

                frame->GetYData(y);
                frame->GetUVData(uv);

                yT->SetDataRedChannel(y, w, h);
                uvT->SetDataRGChannel(uv, w / 2, h / 2);

                free(y);
                free(uv);
            }

            frameDraw->PutUniform1i("pix_fmt", (int)frame->GetPixFormat());
        }

        frameDraw->PutTexture("y", yT, 0);
        frameDraw->PutTexture("u", uT, 1);
        frameDraw->PutTexture("v", vT, 2);
        frameDraw->PutTexture("uv", uvT, 3);

        frameDraw->PutMatrix4fv("mvp", mvp);

        frameDraw->Draw();





        /*

        if(frame->GetPixFormat() == Eyer::EyerAVPixelFormat::Eyer_AV_PIX_FMT_YUVNV12){
            if(frame != nullptr){
                int w = frame->GetWidth();
                int h = frame->GetHeight();
            }
        }

        */

        return 0;
    }
}
