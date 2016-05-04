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

RequestHandler* createLoginHandler(HTTPRequest &request, HandlerSelector *handlerSelector){
    return new Login(request, handlerSelector->db, handlerSelector->tokenManager, handlerSelector->sharedServer);
}

RequestHandler* createSignUpHandler(HTTPRequest& request, HandlerSelector *handlerSelector) {
    return new SignUp(request, handlerSelector->db);
}

RequestHandler* createAuthenticationErrorHandler(HTTPRequest& request, HandlerSelector *handlerSelector) {
    return new AuthenticationError(request);
}

RequestHandler* createMatcherHandler(HTTPRequest& request, HandlerSelector *handlerSelector) {
    return new Matcher(request, handlerSelector->matchesDB, handlerSelector->sharedServer);
}

HandlerSelector::HandlerSelector(std::string sharedAddress) : db("login"), sharedServer(sharedAddress) {
    constructorSelector[HTTP_POST][URI_LOGIN] = createLoginHandler;
    constructorSelector[HTTP_POST][URI_SIGNUP] = createSignUpHandler;
    constructorSelector[HTTP_GET][URI_CANDIDATES] = createMatcherHandler;
}

HandlerSelector::~HandlerSelector() { }

RequestHandler* HandlerSelector::getRequestHandler(HTTPRequest& request) {

    try {
        HandlerConstructor handlerConstructor = constructorSelector[request.getVerb()][request.getUri()];
        return handlerConstructor(request, this);
    } catch (std::exception ex) {
        Json::Value authorization = utils::stringToJson(request.getHeader("Authorization"));
        std::string username = authorization[ID_EMAIL].asString();
        std::string token = authorization[ID_TOKEN].asString();
        if (!tokenManager.isValid(username, token)) {
            return new AuthenticationError(request);
        } else {
            throw ex;
        }
    }
}