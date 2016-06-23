#include <iostream>
#include "MatchRequestHandler.h"
#include "../Exceptions/ParseException.h"
#include "../Exceptions/DatabaseException.h"
#include "../Exceptions/SharedServerException.h"
#include "../MatchData/Threads.h"

#define URI_MATCHES "match"
#define URI_CHAT "chat"
#define URI_USERS "users"

#define REQ_USERS 1
#define REQ_MATCHES 2
#define REQ_CHAT 3

MatchRequestHandler::MatchRequestHandler(SharedProfilesDatabase &sharedData) {

    usersProfiles = new ProfilesDatabase();
    matcher = new Matcher(*usersProfiles);
    chat = new Chat();

    usersProfiles -> setShared(sharedData);

    usersHttp = new UsersHTTP(connected, *usersProfiles, *matcher);
    matcherHttp = new MatchHTTP(*usersProfiles, *matcher, connected);
    chatHttp = new ChatHTTP(*matcher, *chat, connected);

    handlers[URI_USERS] = REQ_USERS;
    handlers[URI_MATCHES] = REQ_MATCHES;
    handlers[URI_CHAT] = REQ_CHAT;
}

HTTPResponse MatchRequestHandler::handle(HTTPRequest &request) {

    std::vector<std::string> uriSplit = request . getSplitUri();

    int requestType = handlers[uriSplit[0]];

    try {

        switch (requestType) {
            case REQ_USERS: {
                std::cout << " >>> USERS <<< " << std::endl;
                return usersHttp -> handle(request);
            }
            case REQ_MATCHES: {
                std::cout << " >>> MATCHES <<< " << std::endl;
                return matcherHttp -> handle(request);
            }
            case REQ_CHAT: {
                std::cout << " >>> CHAT <<< " << std::endl;
                return chatHttp -> handle(request);
            }
            default:
                return HTTP::NotFound();
        }

    } catch (ParseException e) {
        std::cout << "ParseException" << std::endl;
        return HTTP::BadRequest();
    } catch (DatabaseException e) {
        std::cout << "DatabaseException: " << e.what() << std::endl;
        return HTTP::Error(e . what());
    } catch (AuthorizationException e) {
        std::cout << "AuthorizationException: " << e.what() << std::endl;
        return HTTP::Unauthorized();
    } catch (SharedServerException e) {
        std::cout << "SharedServerException: " << e.what() << std::endl;
        return HTTP::Error(e . what());
    } catch (Exception e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return HTTP::Error(e . what());
    }
}