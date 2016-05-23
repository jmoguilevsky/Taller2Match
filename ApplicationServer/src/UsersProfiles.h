//
// Created by chris on 23/05/16.
//

#ifndef APPSERVER_USERSPROFILES_H
#define APPSERVER_USERSPROFILES_H

#include <string>
#include "json/json.h"
#include "UserProfile.h"
#include "SharedData.h"

using namespace std;

class UsersProfiles {
private:

    map<string,string> userId_email_map;
    map<string,string> email_userId_map;
    map<string,string> email_sharedId_map;
    int n;

    string getNextId(){
        n++;
        return std::to_string(n);
    }

    SharedData* sharedData;

public:
    UsersProfiles(){
       n = 0;
    }

    void setShared(SharedData& sharedData){
        this -> sharedData = &sharedData;
    }

    string getUserId(string email){
        return email_userId_map[email];
    }

    bool getProfile(string userId, UserProfile* userProfile){
        if(userId_email_map.count(userId) == 0) return false; // Si no existe ese userId en el app server -> ERROR
        string email = userId_email_map[userId];
        string sharedId = email_sharedId_map[email];
        UserProfile aux;
        bool profileOk = sharedData->getUserProfile(sharedId,&aux);
        if(!profileOk) return false; // Si no existe ese sharedId en el shared server, o hubo otro error -> ERROR
        *userProfile = aux;
        return true; // OK
    }
    bool newUser(UserProfile userProfile, string* userId){
        string email = userProfile.getEmail();
        if(email_sharedId_map.count(email) == 1) return false; // Si ya existe ese email en el app server -> ERROR
        string sharedId;
        bool newUserOk = sharedData->newUser(userProfile,&sharedId);
        if(!newUserOk) return false; // Si no se pudo crear en el shared -> ERROR
        *userId = getNextId();
        email_sharedId_map[email] = sharedId; // Registrar sharedId para ese email
        userId_email_map[*userId] = email; // Registrar email para el userId
        return true;
    }
    bool getUsers(vector<UserProfile>* users){
        vector<UserProfile> aux;
        bool usersOk = sharedData->getUsersList(&aux); // Pido todos los usuarios del shared
        if(!usersOk) return false; // Su hubo algún error en el shared -> ERROR
        for(int i = 0; i < aux.size(); i++){
            if(email_userId_map.count(aux[i].getEmail()) == 1){ // Si existe alguien con ese email acá
                string userId;
                userId = email_userId_map[aux[i].getEmail()];
                aux[i].changeId(userId); // Cambiar el sharedId por el userId del app server
                users->push_back(aux[i]); //Agregar a la lista de los usuarios
            }
        }
        return true;
    }
};


#endif //APPSERVER_USERSPROFILES_H
