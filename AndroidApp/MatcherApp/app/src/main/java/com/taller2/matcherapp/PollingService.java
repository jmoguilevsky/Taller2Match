package com.taller2.matcherapp;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.JsonObjectRequest;
import com.taller2.matcherapp.app.AppConfig;
import com.taller2.matcherapp.app.AppController;
import com.taller2.matcherapp.helper.Alarm;
import com.taller2.matcherapp.helper.Message;
import com.taller2.matcherapp.helper.SQLiteHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;

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
