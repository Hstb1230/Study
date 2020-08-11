package com.example.simple_chat;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.IBinder;

import java.io.IOException;

public class MyService
        extends Service
{
    String nowPlaying;   // 当前播放的文件路径
    MediaPlayer mediaPlayer = null;

    public MyService()
    {
    }

    public class MusicInfoBinder
            extends Binder
    {
        public String getNowPlaying()
        {
            return nowPlaying;
        }

        public void setPlaying(String resourcePath)
        {
            mediaPlayer.reset();
            try
            {
                mediaPlayer.setDataSource(resourcePath);
                mediaPlayer.prepare();
                nowPlaying = resourcePath;
            } catch(IOException e)
            {
                e.printStackTrace();
            }
        }

        public void playing()
        {
            mediaPlayer.start();
        }

        public void pause()
        {
            mediaPlayer.pause();
        }

        public void setTime(int loc)
        {
            mediaPlayer.seekTo(loc * 1000);
        }

        public int getNowLocation()
        {
            return mediaPlayer.getCurrentPosition() / 1000;
        }

        public boolean isPlaying()
        {
            return mediaPlayer.isPlaying();
        }
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        return new MusicInfoBinder();
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
        nowPlaying = "";
        mediaPlayer = new MediaPlayer();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }

}
