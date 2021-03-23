#include "winopenglwidget.h"
#include <QDebug>
#include <QTimer>


#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)
#undef main


GLuint vaoID = 0;
GLuint vboID = 0;
GLuint vboTexID = 0;
GLuint eboID = 0;

GLuint vertexID,fragmentID,programID;

GLuint textureY;
GLuint textureU;
GLuint textureV;

MMAVFream *fream = 0;

winOpenglWidget::winOpenglWidget(QWidget *parent ): QOpenGLWidget(parent)
{
    this->parent = parent;
    resize(parent->width(), parent->height());
}

winOpenglWidget::~winOpenglWidget(){
    if(player != nullptr){
        delete player;
        player = nullptr;
    }

    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &eboID);
}

void winOpenglWidget::setSign(signalPlayer *sign){
    this->playerSign = sign;
}

void winOpenglWidget::createPlayer(){
    if(player == nullptr){
        qDebug() << "createControllerThread ";
        player =new MMPlayer("c://demo/demo1.mp4");
        player->open();
    }

    if(m_pTimer == nullptr){
        m_pTimer = new QTimer(this);
        m_pTimer->setInterval(1);
        connect(m_pTimer, &QTimer::timeout, this, [=](){
             //qDebug() << "m_pTimer is run ";
             if(fream == nullptr){
                if(player->controllerThread->stopFlag == 0){
                    closePlayer();
                }else{
                    player->controllerThread->freamQueue.Pop(&fream);
                    if(fream != nullptr){
                        update();
                    }
                }
             }
        });
        m_pTimer->start();
    }
    isPlay = true;
}

void winOpenglWidget::stopPlayer(){
    isPlay = false;
    if(m_pTimer != nullptr){
        m_pTimer->stop();
        qDebug() << "m_pTimer is stop ";
    }

    if(player != nullptr){
        player->pause();
        qDebug() << "stop player; ";
    }
}

void winOpenglWidget::continuePlayer(){
    isPlay = true;
    if(m_pTimer != nullptr){
        m_pTimer->start();
        qDebug() << "m_pTimer is start ";
    }

    if(player != nullptr){
        player->play();
        qDebug() << "start player; ";
    }
}

void winOpenglWidget::closePlayer(){
    isPlay = false;
    if(m_pTimer != nullptr){
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = nullptr;
        qDebug() << "m_pTimer is delete ";
    }

    if(player != nullptr){
        player->close();
        delete player;
        player = nullptr;
        qDebug() << "delete player; ";
    }

}

void winOpenglWidget::paintGL() {
    if(!isPlay){
        return;
    }

    if(fream == nullptr){
        qDebug() << "fream == nullptr";
        return;
    }
    //std::cout << "playing: " << 1.0 * fream->getFreamTime() / 60000 << std::endl;;
    int width=1920, height=1080;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    {

        glBindVertexArray(vaoID);
        // Y
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureY);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, fream->getYUVData(0));
        glUniform1i(shaderProgram.uniformLocation("y_"), 0);

        // U
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureU);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width / 2, height / 2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, fream->getYUVData(1));
        glUniform1i(shaderProgram.uniformLocation("u_"), 1);

        // V
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureV);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width / 2, height / 2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, fream->getYUVData(2));
        glUniform1i(shaderProgram.uniformLocation("v_"), 2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    shaderProgram.release();
    delete fream;
    fream = nullptr;

}

void winOpenglWidget::initializeGL() {
    initializeOpenGLFunctions();

        // 设置模式


    const char* vertexSource = SHADER(
            \#version 330\n

            layout(location = 0) in vec3 pos;
            layout(location = 1) in vec3 aTexCoord;
            out vec2 texCoord;

        void main() {
            texCoord = vec2(aTexCoord.x, aTexCoord.y);
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        }
    );

    const char* fragmentSource = SHADER(
            \#version 330\n

            uniform sampler2D y_;
            uniform sampler2D u_;
            uniform sampler2D v_;


            in vec2 texCoord;

            out vec4 rgbaColor;

            void main() {
                vec2 t = vec2(texCoord.x, 1.0 - texCoord.y);

                vec3 yuv;
                vec3 rgb;

                yuv.x = texture(y_, t).r;
                // yuv.x = 0;
                yuv.y = texture(u_, t).r-0.5;
                // yuv.y = 0;
                yuv.z = texture(v_, t).r-0.5;
                // yuv.z = 0;

                rgb = mat3(1, 1, 1,
                    0, -0.39465, 2.03211,
                    1.13983, -0.58060, 0) * yuv;

                rgbaColor = vec4(rgb, 1.0);
            }
     );


    shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);

    bool success = shaderProgram.link();
    if(!success) {
            qDebug() << "shaderProgram link failed!";
            shaderProgram.log();
    }


    float vertices[] = {
            // 位置
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,

        };

    GLuint indices[] = { // 注意索引从0开始!
        0,1,2,
        3,2,1

    };

    float texIndicess[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    vaoID = 0;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    // 画三角形坐标
    vboID = 0;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 画三角形顺序
    eboID = 0;
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 纹理坐标
    vboTexID = 0;
    glGenBuffers(1, &vboTexID);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texIndicess), texIndicess, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // 纹理



    glGenTextures(1, &textureY);
    glBindTexture(GL_TEXTURE_2D, textureY);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &textureU);
    glBindTexture(GL_TEXTURE_2D, textureU);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &textureV);
    glBindTexture(GL_TEXTURE_2D, textureV);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


//    // 纹理图片
//    QImage img1 = QImage(":/img/wall.jpg").convertToFormat(QImage::Format_RGB888);
//    if (!img1.isNull()) {
//           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img1.width(), img1.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img1.bits());
//           glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        qDebug() << "img failed!";
//    }
//    glUniform1i(shaderProgram.uniformLocation("textureImg"), 0);

    shaderProgram.release();
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void winOpenglWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}
