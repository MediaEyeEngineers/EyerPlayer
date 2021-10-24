#include "EyerPlayerWidget.h"
#include <stdlib.h>
#include <QDebug>

EyerPlayerWidget::EyerPlayerWidget(QWidget * parent)
    : QOpenGLWidget(parent)
{
    player.Play();
    renderThread = new EyerPlayerRenderThread(&player);

    connect(renderThread, SIGNAL(RenderFrame(void *)), this, SLOT(OnRenderFrame(void *)));

    renderThread->start();
}

EyerPlayerWidget::~EyerPlayerWidget()
{
    if(renderThread != nullptr){
        renderThread->Stop();
        delete renderThread;
        renderThread = nullptr;
    }
    player.Stop();

    if(videoFrame != nullptr){
        delete videoFrame;
        videoFrame = nullptr;
    }
}

void EyerPlayerWidget::initializeGL()
{
    qDebug() << "initializeGL()" << endl;
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1.0);

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

    const char * VERTEX_SHADER = (char *)EYER_GL_HEADER_SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec2 outCoor;

        void main()
        {
            outCoor = vec2(coor.x, 1.0 - coor.y);
            gl_Position = vec4(pos, 1.0);
        }
    );

    const char * FRAGMENT_SHADER = (char *)EYER_GL_HEADER_SHADER(
        out vec4 color;
        in vec2 outCoor;

        uniform sampler2D textY;
        uniform sampler2D textU;
        uniform sampler2D textV;

        void main()
        {
            float y = texture(textY, outCoor).r;
            float u = texture(textU, outCoor).r - 0.5;
            float v = texture(textV, outCoor).r - 0.5;

            mat3 trans = mat3(
                        1.0000, 0.0729, 2.7472,
                        1.0000, -0.4042, -0.9835,
                        1.0001, 2.0173, 0.0464
                        );
            vec3 yuv = vec3(y, u, v);
            vec3 rgb = yuv * trans;
            color = vec4(rgb, 1.0);
        }
    );

    yTexture = new Eyer::EyerGLTexture();
    uTexture = new Eyer::EyerGLTexture();
    vTexture = new Eyer::EyerGLTexture();

    yuvDraw = new Eyer::EyerGLDraw(VERTEX_SHADER, FRAGMENT_SHADER);
    vao = new Eyer::EyerGLVAO();

    vao->AddVBO(vertex, sizeof(vertex), 0);
    vao->AddVBO(coor, sizeof(coor), 1);
    vao->SetEBO(vertexIndex, sizeof(vertexIndex));

    yuvDraw->SetVAO(vao);
}

void EyerPlayerWidget::paintGL()
{
    if(videoFrame != nullptr){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width = videoFrame->GetWidth();
        int height =  videoFrame->GetHeight();

        unsigned char * yData = (unsigned char *)malloc(width * height);
        for(int i=0;i<height;i++){
            memcpy(yData + i * width, videoFrame->GetData(0) + i * videoFrame->GetLinesize(0), width);
        }

        unsigned char * uData = (unsigned char *)malloc(width / 2 * height / 2);
        for(int i=0;i<height / 2;i++){
            memcpy(uData + i * width / 2, videoFrame->GetData(1) + i * videoFrame->GetLinesize(1), width / 2);
        }

        unsigned char * vData = (unsigned char *)malloc(width / 2 * height / 2);
        for(int i=0;i<height / 2;i++){
            memcpy(vData + i * width / 2, videoFrame->GetData(2) + i * videoFrame->GetLinesize(2), width / 2);
        }

        yTexture->SetDataREDChannel(yData, width, height);
        uTexture->SetDataREDChannel(uData, width / 2, height / 2);
        vTexture->SetDataREDChannel(vData, width / 2, height / 2);

        yuvDraw->PutTexture("textY", yTexture, 0);
        yuvDraw->PutTexture("textU", uTexture, 1);
        yuvDraw->PutTexture("textV", vTexture, 2);
        yuvDraw->Draw();

        // qDebug() << "PTS: " << videoFrame->GetSecPTS() << endl;

        if(yData != nullptr){
            free(yData);
            yData = nullptr;
        }
        if(uData != nullptr){
            free(uData);
            uData = nullptr;
        }
        if(vData != nullptr){
            free(vData);
            vData = nullptr;
        }

        delete videoFrame;
        videoFrame = nullptr;
    }
}

void EyerPlayerWidget::resizeGL(int w, int h)
{

}

void EyerPlayerWidget::OnRenderFrame(void * avFrame)
{
    if(videoFrame != nullptr){
        delete videoFrame;
        videoFrame = nullptr;
    }
    videoFrame = (Eyer::EyerAVFrame *)avFrame;
    update();
}
