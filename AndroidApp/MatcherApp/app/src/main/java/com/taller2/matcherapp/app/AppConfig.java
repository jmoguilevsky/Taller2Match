package com.taller2.matcherapp.app;

import android.util.Log;

public class AppConfig {

    public static String app_server_ip = "http://192.168.1.12:7000";

    // Server user login url
    public static String URL_LOGIN = app_server_ip + "/users/login";

    // Server user register url
    public static String URL_REGISTER = app_server_ip + "/users/signup";

    // Server user logout url
    public static String URL_LOGOUT = app_server_ip + "/users/logout";

    // Server user update profile url
    public static String URL_UPDATE_PROFILE = app_server_ip + "/users/update";

    // Server view match profile url
    public static String URL_VIEW_MATCH = app_server_ip + "/match/match";

    // Server find candidate url
    public static String URL_FIND_CANDIDATE = app_server_ip + "/match/candidate";

    // Server like match url
    public static String URL_REACT_CANDIDATE = app_server_ip + "/match/reaction";

    // Server get the new matches url
    public static String URL_GET_NEW_MATCHES = app_server_ip + "/match/new";

    // Server get all the matches url
    public static String URL_GET_ALL_MATCHES = app_server_ip + "/match/matches";

    // Server get all the new messages url
    public static String URL_GET_NEW_MESSAGES = app_server_ip + "/chat/new";

    // Server send a new message url
    public static String URL_SEND_MESSAGE = app_server_ip + "/chat/message";

}
