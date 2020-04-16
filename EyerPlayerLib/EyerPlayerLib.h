/**
 * @file EyerPlayerLib.h
 * @brief 播放器头文件
 * @details 该文件对外的接口
 * @mainpage EyerPlayer
 * @author Redknot
 * @email redknotmiaoyuqiao@gmail.com
 * @version beta 0.1.0
 * @date 2020年4月16日
 */

#ifndef EYERPLAYERLIB_H
#define EYERPLAYERLIB_H

#include "eyerplayerlib_global.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QAudioFormat>
#include <QAudioOutput>

class EYERPLAYERLIBSHARED_EXPORT EyerPlayerLib
{
public:
    EyerPlayerLib();
};

namespace EyerPlayer {

    class StreamInfo;

    class MediaInfo
    {
    public:
        MediaInfo();
        MediaInfo(MediaInfo & mediaInfo);
        ~MediaInfo();

        MediaInfo & operator = (MediaInfo & mediaInfo);

        int AddStreamInfo(StreamInfo & streamInfo);

        int GetStreamCount();
        int GetStream(int index, StreamInfo & streamInfo);


        double duration = 0.0;

    private:
        std::vector<StreamInfo *> streamList;
    };

    enum StreamType
    {
        STREAM_TYPE_UNKNOW = -1,
        STREAM_TYPE_VIDEO = 0,
        STREAM_TYPE_AUDIO = 1
    };

    class StreamInfo
    {
    public:
        StreamType type = StreamType::STREAM_TYPE_UNKNOW;
        int width = 0;
        int height = 0;

        double duration = 0.0;

        int timeBaseNum = 0;
        int timeBaseDen = 0;

        StreamInfo();
        ~StreamInfo();

        StreamInfo(StreamInfo & info);
        StreamInfo & operator = (StreamInfo & info);
    };

    enum EventOpenStatus
    {
        OPEN_STATUS_SUCCESS,
        OPEN_STATUS_FAIL,
        OPEN_STATUS_BUSY
    };

    enum EventStopStatus
    {
        STOP_STATUS_SUCCESS,
        STOP_STATUS_FAIL,
        STOP_STATUS_NOT_OPEN
    };

    /**
     *
     */
    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerCB
    {

    };

    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerOpenCB : public EyerPlayerCB
    {
    public:
        virtual int onOpen(EventOpenStatus status, MediaInfo & videoInfo) = 0;
    };

    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerStopCB : public EyerPlayerCB
    {
    public:
        virtual int onStop(EventStopStatus status) = 0;
    };

    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerProgressCB : public EyerPlayerCB
    {
    public:
        virtual int onProgress(double playTime) = 0;
    };

    class EyerPlayerViewPrivate;


    /**
     * @brief EyerPlayerView 可以作为 Qt 中的一个 QWidget
     * EyerPlayerView 可以作为 Qt 中的一个 QWidget，参与到 Qt 的布局中，操作 EyerPlayerView 就可以播放视频
     */ 
    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
    {
        Q_OBJECT
    public:
        /**
         * @brief 构造函数
         */
        explicit EyerPlayerView(QWidget *parent = nullptr);

        /**
         * @brief 析构函数
         */ 
        ~EyerPlayerView();

        /**
         * @brief 用于初始化 Qt 的 OpenGL 设置
         * @warning 在某些平台上（Mac OS）上，提前全局调用这个函数是必要的，所以建议不管什么平台都调用一次
         */
        static int Init();

        /**
         * @brief 设置要播放资源的路径
         * @details 设置要播放资源的路径，设置后，重新 Open 才能生效
         * @param url 路径（或者网络资源）
         * @return 程序执行成功与否
         *     @retval 0 程序执行成功
         *     @retval -1 程序执行失败
         * @note 别看返回值，一定成功，嘿嘿嘿。。。。
         */
        int SetURL(QString url);

        /**
         * @brief 打开资源
         * @details 打开资源
         * @param openCB 传入一个 Open 回调，来告诉你成功了没有，如果成功，直接就开始播放了
         * @return 执行成功与否
         *     @retval 0 程序执行成功
         *     @retval -1 程序执行失败
         * @note 如果你没有设置 Url，不需要回调，返回值我就给你 return 了。所以调用的时候也要捕获返回值哦。
         */ 
        int Open(EyerPlayerOpenCB * openCB);

        /**
         * @brief 开始播放
         * @details 开始播放
         * @return 执行成功与否
         *     @retval 0 程序执行成功
         *     @retval -1 程序执行失败
         * @note 已经打开成功，并且暂停的情况下才有用。
         */
        int Play();

        /**
         * @brief 开始播放
         * @details 开始播放
         * @return 执行成功与否
         *     @retval 0 程序执行成功
         *     @retval -1 程序执行失败
         * @note 和 Play 是一对
         */
        int Pause();

        /**
         * @brief 停止资源
         * @details 停止资源，停止后，才能重新 Open
         * @param stopCB 传入一个 Stop 回调，来告诉你成功了没有。
         * @return 执行成功与否
         *     @retval 0 程序执行成功
         *     @retval -1 程序执行失败
         * @note 只有在已经 Open 以后，才可以调用
         */ 
        int Stop(EyerPlayerStopCB * stopCB);

        /**
         * @brief 设置一个进度回调
         * @details 设置一个进度回调
         * @param progressCB 传入一个进度回调，来告诉你播放进度。
         * @return 执行成功与否
         * @note 一个 Player 只能设置一个，重复调用会把之前设置的顶掉
         */ 
        int SetProgressCB(EyerPlayerProgressCB * progressCB);

        /**
         * @brief Seek 到某个位置
         * @details Seek 到某个位置
         * @param time 传入要 seek 的时间
         * @return 执行成功与否
         * @note 目前只能 Seek 到 I 帧，不是很精准。想要精准 Seek ？ 求我呀！！！
         */ 
        int Seek(double time);

    protected:
        virtual void initializeGL();
        virtual void resizeGL(int w, int h);
        virtual void paintGL();

        QPaintEngine * paintEngine() const Q_DECL_OVERRIDE;

    private:
        int width = 0;
        int height = 0;

        QString url;

        EyerPlayerViewPrivate * playerViewPrivate = nullptr;

        EyerPlayerProgressCB * progressCB = nullptr;

    private slots:
        void onOpen(int status, long long requestId, MediaInfo * info);
        void onStop(int status, long long requestId);
        void onUpdateUI(int streamId, void * frame);
        void onProgress(double playTime);
    };
}



#endif // EYERPLAYERLIB_H
