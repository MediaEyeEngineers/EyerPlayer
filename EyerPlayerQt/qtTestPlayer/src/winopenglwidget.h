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
protected:
    virtual void paintGL() override;
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;

private:
     bool isPlay = false;
    QWidget *parent = 0;
    QTimer *m_pTimer = 0;
    QOpenGLShaderProgram shaderProgram;
    MMPlayer *player = nullptr;

};

#endif // WINOPENGLWIDGET_H
