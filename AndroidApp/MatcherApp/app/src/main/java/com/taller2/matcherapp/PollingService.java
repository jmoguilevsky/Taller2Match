package com.taller2.matcherapp;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

public class PollingService extends Service {
    public PollingService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
