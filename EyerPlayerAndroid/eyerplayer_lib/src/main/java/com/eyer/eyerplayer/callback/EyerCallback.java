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

    //
    public int onOpen(int videoW, int videoH)
    {
        Message msg = new Message();
        msg.what = MSG_ID_ONOPEN;

        EyerMediaInfo mediaInfo = new EyerMediaInfo();
        mediaInfo.setVideoStreamInfo(videoW, videoH);

        msg.obj = mediaInfo;

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
                EyerMediaInfo mediaInfo = (EyerMediaInfo)msg.obj;
                this.listener.onOpen(mediaInfo);
            }
        }
    }
}
