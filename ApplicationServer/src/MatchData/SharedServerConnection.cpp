//
// Created by chris on 27/04/16.
//

#include "SharedServerConnection.h"
#include "../Log/Log.h"
#include "../Exceptions/DatabaseException.h"
#include "../Exceptions/SharedServerException.h"
#include <iostream>
#include <fstream>

SharedServerConnection::SharedServerConnection(std::string sharedAddress) {
    this->sharedAddress = sharedAddress;
}

vector<UserProfile> SharedServerConnection::getUsersList(){
    MgHTTPClient c;
    bool connectionOk = c.connectToUrl(sharedAddress);
    if(!connectionOk) throw SharedServerException("Could not connect to Shared Server");
    std::map<std::string, std::string> headers;
    headers["Host"] = sharedAddress;
    HTTPRequest request("GET", "/users", headers, "");
    HTTPResponse response = c.sendRequest(request);

    if (response.getCode() != 200) {
        throw SharedServerException ("Could not get users list in Shared Server");
    }

    Json::Value usersList = util::stringToJson(response.getBody());

    vector<UserProfile> users;
    for (int i = 0; i < usersList["users"].size(); i++) {
        UserProfile profile(usersList["users"][i]);
        users.push_back(profile);
    }
    Log::info("Retrieved list of user profiles from shared server.");
    return users;
}

UserProfile SharedServerConnection::getUserProfile(std::string sharedId){
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if(!connectOk) throw SharedServerException("Could not connect to Shared Server");

    std::map<std::string, std::string> headers;
    headers["Host"] = sharedAddress;

    HTTPRequest request("GET", "/users/" + sharedId, headers, "");
    HTTPResponse response = c.sendRequest(request);

    if (response.getCode() != 200) {
        throw SharedServerException ("Could not get user profile from Shared Server");
    }

    Json::Value userJson = util::stringToJson(response.getBody());
    userJson.removeMember("metadata");

    Log::info("Retrieved user profile from shared server");

    return UserProfile(userJson);
}

std::string SharedServerConnection::newUser(UserProfile userProfile) {
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if(!connectOk)  throw SharedServerException("Could not connect to Shared Server");
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

    if (response.getCode() != 201) {
        throw SharedServerException ("Could not create user profile in Shared Server");
    }

    Json::Value userProf = util::stringToJson(response.getBody());
    Log::info("New user created");
    return userProf["user"]["id"].asString();
}

void SharedServerConnection::updateProfile(string sharedId, UserProfile userProfile) {
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if (!connectOk) throw SharedServerException("Could not connect to Shared Server");
    std::map<std::string, std::string> headers;
    headers["Host"] = "enigmatic-depths-58073.herokuapp.com";
    headers["Content-Type"] = "application/json";
    headers["Cache-Control"] = "no-cache";
    std::string profile = util::JsonToString(userProfile.getJson());
    std::stringstream s;

    s << profile.size();
    std::string t;
    s >> t;

    HTTPRequest request("PUT", "/users/" + sharedId, headers, profile);

    HTTPResponse response = c.sendRequest(request);

    std::cout << "RESPONSE: " << response.getCode() << std::endl;

    if (response.getCode() == 201) {
        Log::info("User profile updated");
    } else {
        throw SharedServerException("Could not update user profile in Shared Server");
    }
}

std::vector<Interest> SharedServerConnection::getAllInterests() {
    MgHTTPClient c;
    bool connectOk = c.connectToUrl(sharedAddress);
    if(!connectOk) throw SharedServerException("Could not connect to Shared Server");

    std::map<std::string, std::string> headers;
    headers["Host"] = sharedAddress;

    HTTPRequest request("GET", "/interests", headers, "");
    HTTPResponse response = c.sendRequest(request);

    if (response.getCode() != 200) {
        throw SharedServerException ("Could not get user profile from Shared Server");
    }

    Json::Value interestsJson = util::stringToJson(response.getBody())["interests"];

    std::vector<Interest> interests;
    for (int i = 0; i < interestsJson.size(); i++){
        Interest interest(interestsJson[i]);
        interests.push_back(interest);
    }

    return interests;

}



