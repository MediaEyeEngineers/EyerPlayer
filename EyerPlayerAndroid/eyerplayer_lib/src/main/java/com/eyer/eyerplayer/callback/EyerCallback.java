package com.eyer.eyerplayer.callback;

import android.os.Handler;
import android.os.Message;

import com.eyer.eyerplayer.EyerPlayerListener;
import com.eyer.eyerplayer.mediainfo.EyerMediaInfo;

public class EyerCallback {

    private static final int MSG_ID_ONOPEN = 0x000001;

    private CallbackHandle handle = null;

    public EyerCallback(){

    }

    public EyerCallback(EyerPlayerListener listener){
        handle = new CallbackHandle(listener);
    }

    public int onOpen(int status, int videoW, int videoH)
    {
        if(handle == null){
            return -1;
        }
        Message msg = new Message();
        msg.what = MSG_ID_ONOPEN;

        EyerMediaInfo mediaInfo = new EyerMediaInfo();
        mediaInfo.setVideoStreamInfo(videoW, videoH);

        OpenCallbackInfo openCallbackInfo = new OpenCallbackInfo();
        openCallbackInfo.mediaInfo = mediaInfo;
        openCallbackInfo.openStatus = status;

        msg.obj = openCallbackInfo;

        handle.sendMessage(msg);

        return 0;
    }

    private class CallbackHandle extends Handler
    {
        private EyerPlayerListener listener = null;

        public CallbackHandle(EyerPlayerListener listener){
            this.listener = listener;
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if(msg.what == MSG_ID_ONOPEN){
                OpenCallbackInfo openCallbackInfo = (OpenCallbackInfo)msg.obj;
                this.listener.onOpen(openCallbackInfo.openStatus, openCallbackInfo.mediaInfo);
            }
        }
    }

    private class OpenCallbackInfo
    {
        public int openStatus;
        public EyerMediaInfo mediaInfo;
    }
}
