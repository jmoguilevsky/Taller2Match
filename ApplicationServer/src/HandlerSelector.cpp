#include "HandlerSelector.h"
#include "Handlers/Login.h"
#include "Handlers/SignUp.h"
#include "Handlers/Matcher.h"
#include "Handlers/AuthenticationError.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define URI_LOGIN "/login"
#define URI_SIGNUP "/signup"
#define URI_CANDIDATES "/candidates"
#define ID_TOKEN "token"
#define ID_EMAIL "email"

HandlerSelector::HandlerSelector(std::string sharedAddress) : db("login"), sharedServer(sharedAddress) { }

HandlerSelector::~HandlerSelector() { }

RequestHandler* HandlerSelector::getRequestHandler(HTTPRequest& request) {

    // Recibe un mensaje del cliente, y devuelve el request handler para eso.
    // return RequestHandler(request,dbManager);
    if (request.getVerb() == HTTP_POST && request.getUri() == URI_LOGIN) {
        // Acá como es login, no hay que verificar el token y la autenticación.
        return new Login(request, db, tokenManager, sharedServer);
    }
    //TODO En el resto de los requests, hay que verificar que el token sea válido.
    //TODO Si es inválido -> ERROR!. Si es válido, sigo.

    if (request.getVerb() == HTTP_POST && request.getUri() == URI_SIGNUP) {
        return new SignUp(request, db);
    }

    Json::Value authorization = utils::stringToJson(
            request.getHeader("Authorization"));
    std::string username = authorization[ID_EMAIL].asString();
    std::string token = authorization[ID_TOKEN].asString();
    if (!tokenManager.isValid(username, token)) {
        return new AuthenticationError(request);
    }

    if (request.getVerb() == HTTP_GET && request.getUri() == URI_CANDIDATES) {
        return new Matcher(request, matchesDB, sharedServer);
    }
}