package com.taller2.matcherapp;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.taller2.matcherapp.helper.Alarm;

public class PollingService extends Service {

    public static final String TAG = PollingService.class.getSimpleName();

    Alarm alarm = new Alarm();
    public void onCreate()
    {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        alarm.SetAlarm(this);
        return START_STICKY;
    }

    @Override
    public void onDestroy(){
        alarm.CancelAlarm(this);
    }

    @Override
    public void onStart(Intent intent, int startId)
    {
        alarm.SetAlarm(this);
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        return null;
    }
}
