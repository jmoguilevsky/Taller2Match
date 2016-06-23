//
// Created by chris on 11/06/16.
//

#ifndef APPSERVER_RESPONSEFORMATTER_H
#define APPSERVER_RESPONSEFORMATTER_H


#include "../HTTP/HTTP.h"
#include <iostream>
#include "../Profile/UserProfile.h"
#include "../Utilities/util.h"

//! Este namespace tiene funciones para formatear las respuestas para los distintos requests.

namespace ResponseFormatter {

    HTTPResponse formatViewProfile(UserProfile profile, std::string status);

    HTTPResponse formatLogin(std::string token, UserProfile profile);

    HTTPResponse formatViewProfile(UserProfile profile);

    HTTPResponse formatViewProfile(UserProfile profile);

    HTTPResponse formatGetHistory(std::string history);

    HTTPResponse formatGetHistory(std::string history);
    HTTPResponse formatGetMatches(std::string status);

    HTTPResponse formatGetMatches(std::string status);

    HTTPResponse formatGetCandidate(UserProfile profile);

    HTTPResponse formatGetCandidate(UserProfile profile);

    HTTPResponse formatPostReaction(std::string status);

    HTTPResponse formatPostReaction(std::string status);
};

#endif //APPSERVER_RESPONSEFORMATTER_H
