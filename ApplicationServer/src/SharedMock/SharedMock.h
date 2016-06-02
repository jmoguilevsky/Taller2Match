//
// Created by chris on 02/06/16.
//

#ifndef APPSERVER_SHAREDMOCK_H
#define APPSERVER_SHAREDMOCK_H


#include <cstdbool>
#include "../SharedData.h"
#include "../UserProfile.h"

class SharedMock : public SharedData {
    std::map<std::string, UserProfile> users;
public:
    //! Carga el listado de usuarios en el vector.
    bool getUsersList(vector<UserProfile>* users);

    //! Carga el perfil del usuario con id sharedId.
    bool getUserProfile(string sharedId, UserProfile* userProfile);

    //! Da de alta un nuevo usuario con el perfil, y carga el sharedId con que se creó.
    bool newUser(UserProfile userProfile, string* sharedId);

    //! Actualiza el perfil del usuario con id sharedId.
    bool updateProfile(string sharedId, UserProfile profile);
};


#endif //APPSERVER_SHAREDMOCK_H
