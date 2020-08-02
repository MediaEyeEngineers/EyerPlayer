package com.eyer.eyerplayer;

public interface EyerPlayerViewListener {
    public int beforeCreated();
    public int afterCreated();
    public int beforeDestroyed();
    public int afterDestroyed();
}
