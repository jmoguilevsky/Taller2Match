//
// Created by chris on 27/04/16.
//

#include "SharedServerConnection.h"
#include <iostream>
#include <fstream>

SharedServerConnection::SharedServerConnection(std::string sharedAddress) {
    this->sharedAddress = sharedAddress;
}

bool SharedServerConnection::getUsersList(vector<UserProfile>* users){
    MgHTTPClient c;
    bool connectionOk = c.connectToUrl(sharedAddress);
    if(!connectionOk) return false;
    std::map<std::string, std::string> headers;
    headers["Host"] = sharedAddress;
    HTTPRequest request("GET", "/users", headers, "");
    HTTPResponse response = c.sendRequest(request);

    if(response.getCode() != 200) return false;

    Json::Value usersList = util::stringToJson(response.getBody());

    for (int i = 0; i < usersList["users"].size(); i++) {
        UserProfile profile(usersList["users"][i]);
        users->push_back(profile);
    }

    return true;
}

bool SharedServerConnection::getUserProfile(std::string sharedId, UserProfile* userProfile){
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if(!connectOk) return false;

    std::map<std::string, std::string> headers;
    headers["Host"] = sharedAddress;

    HTTPRequest request("GET", "/users/" + sharedId, headers, "");
    HTTPResponse response = c.sendRequest(request);

    if(response.getCode() != 200)return false;

    std::cout << "response: " << response.getBody() << std::endl;

    Json::Value userJson = util::stringToJson(response.getBody());
    userJson.removeMember("metadata");

    std::string userJsonStr = util::JsonToString(userJson);

    userProfile -> fromJson(userJsonStr);

    return true;
}

bool SharedServerConnection::newUser(UserProfile userProfile, std::string* sharedId){
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if(!connectOk) return false;
    std::map<std::string, std::string> headers;
    headers["Host"] = "enigmatic-depths-58073.herokuapp.com";
    headers["Content-Type"] = "application/json";
    headers["Cache-Control"] = "no-cache";
    std::string profile = util::JsonToString(userProfile.getJson());
    std::stringstream s;

    s << profile.size();
    std::string t;
    s >> t;

    HTTPRequest request("POST", "/users", headers, profile);

    HTTPResponse response = c.sendRequest(request);

    if(response.getCode() != 201) return false;

    Json::Value userProf = util::stringToJson(response.getBody());
    *sharedId = userProf["user"]["id"].asString();

    return true;
}