package com.taller2.matcherapp.app;

/**
 * Created by seba on 24/04/16.
 */
public class AppConfig {
    // Server user login url
    public static String URL_LOGIN = "http://10.0.2.2:7000/users/login";

    // Server user register url
    public static String URL_REGISTER = "http://10.0.2.2:7000/users/signup";

    // Server user logout url
    public static String URL_LOGOUT = "http://10.0.2.2:7000/users/logout";

    // Server user update profile url
    public static String URL_UPDATE_PROFILE = "http://10.0.2.2:7000/users/update";

    // Server view match profile url
    public static String URL_VIEW_MATCH = "http://10.0.2.2:7000/match/match";

    // Server find candidate url
    public static String URL_FIND_CANDIDATE = "http://10.0.2.2:7000/match/candidate";

    //Server like match url
    public static String URL_LIKE_CANDIDATE = "http://10.0.2.2:7000/match";

}
