#ifndef EYERPLAYERWIDGET_H
#define EYERPLAYERWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <EyerPlayer/EyerPlayer.hpp>
#include <EyerGL/EyerGL.hpp>

#include "EyerPlayerRenderThread.h"

class EyerPlayerWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit EyerPlayerWidget(QWidget *parent = nullptr);
    ~EyerPlayerWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private slots:
    void OnRenderFrame(void * avFrame);

private:


    Eyer::EyerPlayer player;

    EyerPlayerRenderThread * renderThread = nullptr;

    Eyer::EyerGLDraw * yuvDraw = nullptr;
    Eyer::EyerGLVAO * vao = nullptr;

    Eyer::EyerGLTexture * yTexture = nullptr;
    Eyer::EyerGLTexture * uTexture = nullptr;
    Eyer::EyerGLTexture * vTexture = nullptr;

    Eyer::EyerAVFrame * videoFrame = nullptr;
};

#endif // EYERPLAYERWIDGET_H
