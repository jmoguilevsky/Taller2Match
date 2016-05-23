#include "MatchRequestHandler.h"

#define URI_MATCHES "matches"
#define URI_CHAT "chat"
#define URI_USERS "users"

#define REQ_USERS 1
#define REQ_MATCHES 2
#define REQ_CHAT 3

MatchRequestHandler::MatchRequestHandler(SharedData &sharedData) {

    // Esto podría salir y que se pasen user matches y chat por parámetro.

    users = new Users(sharedData);
    matches = new Matcher(sharedData);
    chat = new Chat();

    // TODOS necesitan Users para saber si el token es válido o no.
    // UsersHTTP necesita Matcher para que un usuario no pueda pedir el perfil de otro usuario si no es un match.
    // ChatHTTP necesita Matcher para que un usuario no pueda mandar un chat a otro usuario si no es un match.

    usersHttp = new UsersHTTP(*users, *matches);
    matcherHttp = new MatcherHTTP(*users,*matches);
    chatHttp = new ChatHTTP(*users,*matches, *chat);

    handlers[URI_USERS] = REQ_USERS;
    handlers[URI_MATCHES] = REQ_MATCHES;
    handlers[URI_CHAT] = REQ_CHAT;
}

HTTPResponse MatchRequestHandler::handle(HTTPRequest &request) {

    std::vector<std::string> uriSplit = request.getSplitUri();

    std::cout << "URI: " << request.getUri() << std::endl;

    int requestType = handlers[uriSplit[0]];

    switch (requestType) {
        case REQ_USERS:
            std::cout << " >>> USERS <<< " << std::endl;
            return usersHttp->handle(request);
        case REQ_MATCHES:
            std::cout << " >>> MATCHES <<< " << std::endl;
            return matcherHttp->handle(request);
        case REQ_CHAT:
            std::cout << " >>> CHAT <<< " << std::endl;
            return chatHttp->handle(request);
        default:
            return HTTP::NotFound();
    }
}