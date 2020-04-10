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

    class EYERPLAYERLIBSHARED_EXPORT EyerPlayerView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
    {
        Q_OBJECT
    public:
        explicit EyerPlayerView(QWidget *parent = nullptr);
        ~EyerPlayerView();

        static int Init();

        int SetURL(QString url);

        int Open(EyerPlayerOpenCB * openCB);
        int Play();
        int Pause();
        int Stop(EyerPlayerStopCB * stopCB);

        int SetProgressCB(EyerPlayerProgressCB * progressCB);

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
