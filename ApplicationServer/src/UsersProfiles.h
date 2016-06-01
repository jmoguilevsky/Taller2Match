//
// Created by chris on 23/05/16.
//

#ifndef APPSERVER_USERSPROFILES_H
#define APPSERVER_USERSPROFILES_H

#include <string>
#include "json/json.h"
#include "UserProfile.h"
#include "SharedData.h"
#include "DB/RocksDB.h"

using namespace std;

class UsersProfiles {
private:

    RocksDB *userId_email_map;
    RocksDB *email_userId_map;
    RocksDB *email_sharedId_map;
    int n;

    string getNextId();

    SharedData* sharedData;

public:
    UsersProfiles();

    void setShared(SharedData &sharedData);

    string getUserId(string email);

    bool getProfile(string userId, UserProfile *userProfile);

    bool newUser(UserProfile userProfile, string *userId);

    bool getUsers(vector<UserProfile> *users);
};


#endif //APPSERVER_USERSPROFILES_H
