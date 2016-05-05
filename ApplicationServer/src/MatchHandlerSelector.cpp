#include "MatchHandlerSelector.h"
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

// TODO: Para cada una de estas funciones, chequear los casos de error.

Handler * MatchHandlerSelector::createLoginHandler(HTTPRequest &request) {
    return new Login(request, dbManager.getLoginDB(), tokenManager, sharedData);
}

Handler * MatchHandlerSelector::createSignUpHandler(HTTPRequest &request) {
    return new SignUp(request,dbManager.getLoginDB());
}

Handler * MatchHandlerSelector::createAuthenticationErrorHandler(HTTPRequest &request) {
    return new AuthenticationError(request);
}

Handler * MatchHandlerSelector::createMatcherHandler(HTTPRequest &request) {
    return new Matcher(request, dbManager.getMatchesDB(),sharedData);
}

MatchHandlerSelector::MatchHandlerSelector(DBManager& dbManager, SharedData& sharedData): dbManager(dbManager),sharedData(sharedData) {
    constructorSelector[HTTP_POST][URI_LOGIN] =&MatchHandlerSelector::createLoginHandler;
    constructorSelector[HTTP_POST][URI_SIGNUP] = &MatchHandlerSelector::createSignUpHandler;
    constructorSelector[HTTP_GET][URI_CANDIDATES] = &MatchHandlerSelector::createMatcherHandler;
}

MatchHandlerSelector::~MatchHandlerSelector() { }


Handler* MatchHandlerSelector::getRequestHandler(HTTPRequest& request) {
	try {
		Handler* (MatchHandlerSelector::*handlerConstructor)(HTTPRequest &) = constructorSelector[request.getVerb()][request.getUri()];
		Handler* handler = (this->*handlerConstructor)(request);
		return handler;
	} catch (std::exception ex) {
		Json::Value authorization = utils::stringToJson(
				request.getHeader("Authorization"));
		std::string username = authorization[ID_EMAIL].asString();
		std::string token = authorization[ID_TOKEN].asString();
		if (!tokenManager.isValid(username, token)) {
			return new AuthenticationError(request);
		} else {
			throw ex;
		}
	}
}