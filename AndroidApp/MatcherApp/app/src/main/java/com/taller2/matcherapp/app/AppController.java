package com.taller2.matcherapp.app;

import android.app.Application;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;

import com.android.volley.DefaultRetryPolicy;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.Volley;

import java.io.ByteArrayOutputStream;

public class AppController extends Application {
    public static final String TAG = AppController.class.getSimpleName();

    private RequestQueue mRequestQueue;

    private String app_server_ip;

    private static AppController mInstance;

    @Override
    public void onCreate() {
        super.onCreate();
        mInstance = this;
    }

    public static synchronized AppController getInstance() {
        return mInstance;
    }

    public RequestQueue getRequestQueue() {
        if (mRequestQueue == null) {
            mRequestQueue = Volley.newRequestQueue(getApplicationContext());
        }

        return mRequestQueue;
    }

    public <T> void addToRequestQueue(Request<T> req, String tag) {
        req.setTag(TextUtils.isEmpty(tag) ? TAG : tag);
        req.setRetryPolicy(new DefaultRetryPolicy(
                3500,
                DefaultRetryPolicy.DEFAULT_MAX_RETRIES,
                DefaultRetryPolicy.DEFAULT_BACKOFF_MULT));
        getRequestQueue().add(req);
    }

    public <T> void addToRequestQueue(Request<T> req) {
        req.setTag(TAG);
        getRequestQueue().add(req);
    }

    public void cancelPendingRequests(Object tag) {
        if (mRequestQueue != null) {
            mRequestQueue.cancelAll(tag);
        }
    }

    public Bitmap getBitmapImage (String image_string){
        // Function that decodes a base_64 string into a bitmap.
        byte[] decodedString = Base64.decode(image_string, Base64.DEFAULT);
        return BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
    }

    public String getStringImage(Bitmap bmp){
        // Function that encodes a bitmap into a base_64 string.
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bmp.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        byte[] imageBytes = baos.toByteArray();
        return Base64.encodeToString(imageBytes, Base64.DEFAULT);
    }

    public void cambiarIP(String ip){
        app_server_ip = "http://".concat(ip).concat(":7000");
        Log.d("AppC",app_server_ip);
    }

    public String getLogin(){
        return app_server_ip.concat("/users/login");
    }

    public String getRegister(){
        return app_server_ip.concat("/users/signup");
    }

    public String getLogout(){
        return app_server_ip.concat("/users/logout");
    }

    public String getUpdateProfile(){
        return app_server_ip.concat("/users/update");
    }

    public String getViewMatch(){
        return app_server_ip.concat("/match/match");
    }

    public String getFindCandidate(){
        return app_server_ip.concat("/match/candidate");
    }

    public String getReactCandidate(){
        return app_server_ip.concat("/match/reaction");
    }

    public String getNewMatches(){
        return app_server_ip.concat("/match/new");
    }

    public String getAllMatches(){
        return app_server_ip.concat("/match/matches");
    }

    public String getNewMessages(){
        return app_server_ip.concat("/chat/new");
    }

    public String getSendMessage(){
        return app_server_ip.concat("/chat/message");
    }
}
