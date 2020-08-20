package com.eyer.eyerplayer.callback;

import android.os.Handler;
import android.os.Message;

import com.eyer.eyerplayer.EyerPlayerListener;

public class EyerCallback {

    private static final int MSG_ID_ONOPEN = 0x000001;

    private CallbackHandle handle = null;

    public EyerCallback(EyerPlayerListener listener){
        handle = new CallbackHandle(listener);
    }

    // 该函数被子线程调用
    public int onOpen()
    {
        Message msg = new Message();
        msg.what = MSG_ID_ONOPEN;
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
                this.listener.onOpen();
            }
        }
    }
}
