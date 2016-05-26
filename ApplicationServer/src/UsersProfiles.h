//
// Created by chris on 23/05/16.
//

#ifndef APPSERVER_USERSPROFILES_H
#define APPSERVER_USERSPROFILES_H

#include <string>
#include "json/json.h"
#include "UserProfile.h"
#include "SharedData.h"
#include "DB/RocksDb.h"

using namespace std;

class UsersProfiles {
private:

    RocksDb *userId_email_map;
    RocksDb *email_userId_map;
    RocksDb *email_sharedId_map;
    int n;

    string getNextId();

    SharedData* sharedData;

public:
    UsersProfiles();

    void setShared(SharedData &sharedData);

    string getUserId(string email);

    bool getProfile(string userId, UserProfile *userProfile);

    bool newUser(UserProfile userProfile, string *userId);

    bool getUsers(map<string, UserProfile> *users);
};


#endif //APPSERVER_USERSPROFILES_H
