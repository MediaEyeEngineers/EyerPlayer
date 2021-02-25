#include "EyerPlayer.hpp"

#include "EyerPlayerPrivate.hpp"
#include "PlayerEvent.hpp"

namespace Eyer
{
    EyerPlayer::EyerPlayer()
    {
        piml = new EyerPlayerPrivate();

        piml->eventManager = new EyerPlayerEventManager();
        piml->eventManager->Start();
    }

    EyerPlayer::~EyerPlayer()
    {
        if(piml->eventManager != nullptr){
            piml->eventManager->Stop();
            delete piml->eventManager;
            piml->eventManager = nullptr;
        }
        if(piml != nullptr){
            delete piml;
            piml = nullptr;
        }
    }

    int EyerPlayer::Open(std::string url, const EyerPlayerConfig & playerConfig)
    {
        piml->url = url;
        piml->playerConfig = playerConfig;

        long long requestId = piml->eventManager->GenId();

        EventOpenRequest * event = new EventOpenRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->url = url.c_str();
        event->playerConfig = piml->playerConfig;
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Play()
    {
        long long requestId = piml->eventManager->GenId();

        EventPlayRequest * event = new EventPlayRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Pause()
    {
        long long requestId = piml->eventManager->GenId();

        EventPauseRequest * event = new EventPauseRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);
        return 0;
    }

    int EyerPlayer::Stop()
    {
        long long requestId = piml->eventManager->GenId();

        EventStopRequest * event = new EventStopRequest();
        event->SetFrom(EventTag::PLAYER);
        event->SetTo(EventTag::EVENT_MANAGER);
        event->SetRequestId(requestId);

        piml->eventManager->PushEvent(event);

        return 0;
    }

    int EyerPlayer::Seek(double time)
    {
        long long requestId = piml->eventManager->GenId();

        EventSeekRequest * seekRequest = new EventSeekRequest();
        seekRequest->SetFrom(EventTag::PLAYER);
        seekRequest->SetTo(EventTag::EVENT_MANAGER);
        seekRequest->SetRequestId(requestId);
        seekRequest->time = time;
        piml->eventManager->PushEvent(seekRequest);

        return 0;
    }

    int EyerPlayer::SwitchRepresentation(int representationId)
    {
        long long requestId = piml->eventManager->GenId();

        EventSwitchRepresentationRequest * switchRepresentationRequest = new EventSwitchRepresentationRequest();
        switchRepresentationRequest->SetFrom(EventTag::PLAYER);
        switchRepresentationRequest->SetTo(EventTag::EVENT_MANAGER);
        switchRepresentationRequest->SetRequestId(requestId);
        piml->eventManager->PushEvent(switchRepresentationRequest);

        return 0;
    }

    int EyerPlayer::BindGLContext(Eyer::EyerGLContextThread * ctx)
    {
        return piml->eventManager->SetGLCtx(ctx);
    }

    int EyerPlayer::UnBindGLContext()
    {
        return piml->eventManager->UnbindGLCtx();
    }

    int EyerPlayer::SetSurface(jobject _surface)
    {
        return piml->eventManager->SetSurface(_surface);
    }

    int EyerPlayer::SetCallback(EyerPlayerCallback * callback)
    {
        return piml->eventManager->SetCallback(callback);
    }

    int EyerPlayer::RenderInit()
    {
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return 0;
    }

    int EyerPlayer::RenderDraw(int texId)
    {
        // 软件渲染
        AVFrameQueueManager * frameQueueManager = piml->eventManager->GetEyerPlayerThreadManager()->GetAVFrameQueueManager();

        AVFrameQueue * videoRenderFrameQueue = nullptr;
        frameQueueManager->GetQueue(EventTag::FRAME_QUEUE_RENDER_VIDEO, &videoRenderFrameQueue);

        if(videoRenderFrameQueue != nullptr){
            EyerAVFrame * frame = nullptr;
            videoRenderFrameQueue->FrontPop(&frame);
            if(frame != nullptr){
                // EyerLog("wwwwwwwww Render\n");
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                piml->yuvRenderTask = new YUVRenderTask();
                piml->yuvRenderTask->SetFrame(frame);
                piml->yuvRenderTask->Init();
                piml->yuvRenderTask->SetWH(100, 100);
                piml->yuvRenderTask->Render();
                piml->yuvRenderTask->SetFrame(nullptr);
                delete piml->yuvRenderTask;
                if(frame != nullptr){
                    delete frame;
                    frame = nullptr;
                }
            }
        }

        return 0;
    }
}