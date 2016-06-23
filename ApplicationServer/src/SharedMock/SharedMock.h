//
// Created by chris on 02/06/16.
//

#ifndef APPSERVER_SHAREDMOCK_H
#define APPSERVER_SHAREDMOCK_H


#include <cstdbool>
#include "../Profile/UserProfile.h"
#include "../MatchData/SharedProfilesDatabase.h"
#include "../DB/RocksDb.h"

class SharedMock : public SharedProfilesDatabase {
    std::map<std::string, UserProfile> users;
    RocksDb* db;
public:
    SharedMock(){
         db = new RocksDb("usersProfiles");
    }

     std::vector<UserProfile> getUsersList() ;

    //! Carga el perfil del usuario con id sharedId.
     UserProfile getUserProfile(std::string sharedId) ;

    //! Da de alta un nuevo usuario con el perfil, y carga el sharedId con que se creó.
     std::string newUser(UserProfile userProfile) ;

    //! Actualiza el perfil del usuario con id sharedId.
     void updateProfile(string sharedId, UserProfile profile) ;

    std::vector<Interest> getAllInterests();
};


#endif //APPSERVER_SHAREDMOCK_H
