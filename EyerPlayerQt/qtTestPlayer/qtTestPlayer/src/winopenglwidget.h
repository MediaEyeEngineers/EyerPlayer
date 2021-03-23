#ifndef WINOPENGLWIDGET_H
#define WINOPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QString>
#include <QTimer>

#include "MMPlayer/MMPlayer.h"
#include "MMThread/MMThread.h"
#include "signalplayer.h"

class winOpenglWidget:  public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    winOpenglWidget(QWidget *parent = nullptr);
    ~winOpenglWidget();

    void createPlayer();
    void stopPlayer();
    void continuePlayer();
    void closePlayer();

    void setSign(signalPlayer *uiSign);

protected:
    virtual void paintGL() override;
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;

private:
    signalPlayer *playerSign;

    bool isPlay = false;

    QWidget *parent = nullptr;
    QTimer *m_pTimer = nullptr;

    QOpenGLShaderProgram shaderProgram;
    MMPlayer *player = nullptr;

};

#endif // WINOPENGLWIDGET_H
