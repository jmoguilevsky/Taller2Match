package com.taller2.matcherapp.app;

/**
 * Created by seba on 24/04/16.
 */
public class AppConfig {
    // Server user login url: POST
    public static String URL_LOGIN = "http://10.0.2.2:7000/users/login";

    // Server user register url: POST
    public static String URL_REGISTER = "http://10.0.2.2:7000/users/signup";

    // Server update user profile url: PUT
    public static String URL_UPDATE = "http://10.0.2.2:7000/users/update";

    // Server find candidate url: GET
    public static String URL_FIND_CANDIDATE = "http://10.0.2.2:7000/users/match/update";
}
