#include "EyerPlayerLib.h"
#include <QDebug>

#include "EyerCore/EyerCore.hpp"
#include "EyerGL/EyerGL.hpp"
#include "PlayerEvent.hpp"
#include "EyerPlayerEventManager.h"
#include "EyerPlayerViewPrivate.h"
#include "EyerPlayerVideoRender.h"

#include <QAudioFormat>
#include <QAudioOutput>

namespace EyerPlayer {

    int EyerPlayerView::Init(){

        // EyerLog("EyerPlayerView Init\n");

        QSurfaceFormat format;
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        format.setVersion(3, 3);
        format.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(format);

        return 0;
    }

    EyerPlayerView::EyerPlayerView(QWidget * parent) : QOpenGLWidget(parent)
    {
        playerViewPrivate = new EyerPlayerViewPrivate();

        playerViewPrivate->frameQueueManager= new AVFrameQueueManager();
        playerViewPrivate->eventManager     = new EyerPlayerEventManager(playerViewPrivate->frameQueueManager);

        playerViewPrivate->openCBmap        = new std::map<long long, EyerPlayerOpenCB *>();
        playerViewPrivate->stopCBmap        = new std::map<long long, EyerPlayerStopCB *>();

        playerViewPrivate->audioPlayThread  = new AudioPlayThread(playerViewPrivate->eventManager->eventQueue, playerViewPrivate->frameQueueManager);

        connect(playerViewPrivate->eventManager, SIGNAL(onOpen(int, long long)),    this, SLOT(onOpen(int, long long)),         Qt::AutoConnection);
        connect(playerViewPrivate->eventManager, SIGNAL(onStop(int, long long)),    this, SLOT(onStop(int, long long)),         Qt::AutoConnection);
        connect(playerViewPrivate->eventManager, SIGNAL(onUpdateUI(int, void *)),   this, SLOT(onUpdateUI(int, void *)),        Qt::AutoConnection);

        playerViewPrivate->eventManager->start();
        playerViewPrivate->audioPlayThread->Detach();



        QAudioFormat audioFormat;
        audioFormat.setSampleRate(48000);
        audioFormat.setChannelCount(2);
        audioFormat.setSampleSize(16);
        audioFormat.setCodec("audio/pcm");
        audioFormat.setByteOrder(QAudioFormat::LittleEndian);
        audioFormat.setSampleType(QAudioFormat::SignedInt);

        audioOutput = new QAudioOutput(audioFormat, this);
        streamOut = audioOutput->start();
    }

    EyerPlayerView::~EyerPlayerView()
    {
        // Stop Audio play thread
        if(playerViewPrivate->audioPlayThread != nullptr){
            playerViewPrivate->audioPlayThread->Stop();
            delete playerViewPrivate->audioPlayThread;
            playerViewPrivate->audioPlayThread = nullptr;
        }

        // Stop event manager thread
        if(playerViewPrivate->eventManager != nullptr){
            playerViewPrivate->eventManager->Stop();
            delete playerViewPrivate->eventManager;
            playerViewPrivate->eventManager = nullptr;
        }

        // Delete Callback
        if(playerViewPrivate->openCBmap != nullptr){
            playerViewPrivate->openCBmap->clear();
            delete playerViewPrivate->openCBmap;
            playerViewPrivate->openCBmap = nullptr;
        }

        if(playerViewPrivate->stopCBmap != nullptr){
            playerViewPrivate->stopCBmap->clear();
            delete playerViewPrivate->stopCBmap;
            playerViewPrivate->stopCBmap = nullptr;
        }

        // Delete render video util
        if(playerViewPrivate->videoRender != nullptr){
            delete playerViewPrivate->videoRender;
            playerViewPrivate->videoRender = nullptr;
        }

        // delete frame queue manager
        // TODO Free all queue
        if(playerViewPrivate->frameQueueManager != nullptr){
            delete playerViewPrivate->frameQueueManager;
            playerViewPrivate->frameQueueManager = nullptr;
        }

        if(playerViewPrivate != nullptr){
            delete playerViewPrivate;
            playerViewPrivate = nullptr;
        }
    }

    QPaintEngine * EyerPlayerView::paintEngine() const
    {
        return 0;
    }

    void EyerPlayerView::initializeGL()
    {
        initializeOpenGLFunctions();
        glClearColor(0.0, 0.0, 0.0, 1.0);

        playerViewPrivate->videoRender = new EyerPlayerVideoRender(this);
    }

    void EyerPlayerView::resizeGL(int w, int h)
    {
        width = w;
        height = h;
    }

    void EyerPlayerView::paintGL()
    {
        // Find player video frame queue
        AVFrameQueue * playerVideoFrameQueue = nullptr;
        playerViewPrivate->frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_VIDEO, &playerVideoFrameQueue);
        if(playerVideoFrameQueue == nullptr){
            return;
        }

        while(playerVideoFrameQueue->Size() > 5){
            Eyer::EyerAVFrame * f = nullptr;
            playerVideoFrameQueue->FrontPop(&f);
            if(f != nullptr){
                delete f;
            }
        }

        Eyer::EyerAVFrame * f = nullptr;
        playerVideoFrameQueue->FrontPop(&f);
        if(f == nullptr){
            return;
        }

        makeCurrent();
#ifdef Q_OS_OSX
        glViewport(0, 0, width * 2, height * 2);
#else
        glViewport(0, 0, width, height);
#endif


        glClear(GL_COLOR_BUFFER_BIT);

        playerViewPrivate->videoRender->Viewport(width, height);
        playerViewPrivate->videoRender->SetFrame(f);

        Eyer::EyerMat4x4 ortho;
        ortho.SetOrtho(-width / 2.0, width / 2.0, height / 2.0, -height / 2.0, 0.0, 1000.0f);

        Eyer::EyerAVCropUtil cropUtil;
        int imageW = 200;
        int imageH = 200;

        cropUtil.GetCrop(width / 2, height / 2, f->GetWidth(), f->GetHeight(), imageW, imageH, Eyer::EyerAVCropType::FIT_CENTER);


        Eyer::EyerMat4x4 scale;
        scale.SetScale(imageW, imageH, 1.0);

        Eyer::EyerMat4x4 mvp = ortho * scale;

        playerViewPrivate->videoRender->SetMVP(mvp);

        playerViewPrivate->videoRender->Draw();

        delete f;

        if(playerVideoFrameQueue->Size() > 0){
            update();
        }
    }


    int EyerPlayerView::SetURL(QString _url)
    {
        url = _url;
        return 0;
    }

    int EyerPlayerView::Open(EyerPlayerOpenCB * openCB)
    {
        long long requestId = playerViewPrivate->eventManager->GenId();

        playerViewPrivate->openCBmap->insert(std::pair<long long, EyerPlayerOpenCB *>(requestId, openCB));

        EventOpenRequest * event = new EventOpenRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->url = url.toStdString().c_str();
        event->SetRequestId(requestId);

        playerViewPrivate->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayerView::Play()
    {
        return 0;
    }

    int EyerPlayerView::Pause()
    {
        return 0;
    }

    int EyerPlayerView::Stop(EyerPlayerStopCB * stopCB)
    {
        long long requestId = playerViewPrivate->eventManager->GenId();

        playerViewPrivate->stopCBmap->insert(std::pair<long long, EyerPlayerStopCB *>(requestId, stopCB));

        EventStopRequest * event = new EventStopRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        playerViewPrivate->eventManager->PushEvent(event);

        return 0;
    }


    void EyerPlayerView::onOpen(int status, long long requestId)
    {
        std::map<long long, EyerPlayerOpenCB *>::iterator iter = playerViewPrivate->openCBmap->find(requestId);
        if(iter != playerViewPrivate->openCBmap->end()) {
            VideoInfo videoInfo;
            iter->second->onOpen((EventOpenStatus)status, videoInfo);
        }
        else{

        }
    }

    void EyerPlayerView::onStop(int status, long long requestId)
    {
        std::map<long long, EyerPlayerStopCB *>::iterator iter = playerViewPrivate->stopCBmap->find(requestId);
        if(iter != playerViewPrivate->stopCBmap->end()) {
            iter->second->onStop((EventStopStatus)status);
        }
        else{

        }
    }

    void EyerPlayerView::onUpdateUI(int streamId, void * frame)
    {
        if(streamId == 0){
            AVFrameQueue * playerVideoFrameQueue = nullptr;
            playerViewPrivate->frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_VIDEO, &playerVideoFrameQueue);
            if(playerVideoFrameQueue == nullptr){
                return;
            }

            Eyer::EyerAVFrame * f = (Eyer::EyerAVFrame *)frame;
            playerVideoFrameQueue->Push((Eyer::EyerAVFrame *)frame);
            update();
        }

        /*
        if(streamId == 1){
            Eyer::EyerAVFrame * f = (Eyer::EyerAVFrame *)frame;
            qDebug() << f->timePts << endl;

            AVFrameQueue * playerAudioFrameQueue = nullptr;
            playerViewPrivate->frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_PLAYER_AUDIO, &playerAudioFrameQueue);
            if(playerAudioFrameQueue != nullptr){
                playerAudioFrameQueue->Push(f);
            }

            if(playerAudioFrameQueue != nullptr){
                if(streamOut->isWritable()){
                    Eyer::EyerAVFrame * f = nullptr;
                    playerAudioFrameQueue->FrontPop(&f);
                    if(f != nullptr){
                        int len = f->GetAudioPackedData(nullptr);
                        unsigned char * data = (unsigned char *)malloc(len);
                        f->GetAudioPackedData(data);

                        int alreadyWrited = 0;
                        while(alreadyWrited < len){
                            int ret = streamOut->write((char *)data + alreadyWrited, len - alreadyWrited);
                            alreadyWrited += ret;
                        }

                        // qDebug() << ret << endl;

                        free(data);

                        delete f;
                    }
                }
            }
        }
        */
    }
}
