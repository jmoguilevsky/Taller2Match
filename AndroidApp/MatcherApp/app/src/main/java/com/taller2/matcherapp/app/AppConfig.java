package com.taller2.matcherapp.app;

/**
 * Created by seba on 24/04/16.
 */
public class AppConfig {
    public static String app_server_ip = "http://192.168.43.246:7000";

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

    //Server like match url
    public static String URL_REACT_CANDIDATE = app_server_ip + "/match";

}
