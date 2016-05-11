#include "MatchRequestHandler.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define URI_LOGIN "/login"
#define URI_SIGNUP "/signup"
#define URI_CANDIDATES "/candidates"
#define URI_LIKE "/like"
#define URI_MATCHES "/matches"
#define URI_NOMATCH "/nomatch"

#define REQ_SIGN_UP 0
#define REQ_LOGIN 1
#define REQ_GET_CANDIDATES 2
#define REQ_LIKE 3
#define REQ_NO_MATCH 4
#define REQ_SEND_CHAT 5
#define REQ_GET_UNREAD 6
#define REQ_LOGOUT 7

#define ID_TOKEN "token"
#define ID_EMAIL "email"

// TODO: Para cada una de estas funciones, chequear los casos de error.

MatchRequestHandler::MatchRequestHandler(DBManager &dbManager, SharedData &sharedData) : signUp(dbManager.getLoginDB(),
                                                                                                sharedData),
                                                                                         login(dbManager.getLoginDB(),
                                                                                               sharedData),
                                                                                         chat(dbManager.getChatDB()),
                                                                                         matcher(dbManager.getMatchesDB(),
                                                                                                 sharedData) {
	handlers[HTTP_POST][URI_LOGIN] = REQ_LOGIN;
	handlers[HTTP_POST][URI_SIGNUP] = REQ_SIGN_UP;
	handlers[HTTP_POST][URI_LIKE] = REQ_LIKE;
	handlers[HTTP_POST][URI_NOMATCH] = REQ_NO_MATCH;
	handlers[HTTP_GET][URI_CANDIDATES] = REQ_GET_CANDIDATES;

}

MatchRequestHandler::~MatchRequestHandler() { }

bool parseLoginRequest(HTTPRequest request, std::string &user, std::string &pass) {
	Json::Value userInfo(request.getBody());
	user = userInfo["user"]["email"].asString();
	pass = userInfo["user"]["password"].asString();
	return true;
}

bool parseSignUpRequest(HTTPRequest request, std::string &email, std::string &password, UserProfile &userProfile) {
	Json::Value userInfo = utils::stringToJson(request.getBody());
	email = userInfo["user"]["email"].asString();
	password = userInfo["user"]["password"].asString();
	userProfile.fromJson(userInfo["user"]);
	return true;
}

bool parseLikeRequest(HTTPRequest request, std::string &userA, std::string &userB) {
	return true;
}

bool parseNoMatchRequest(HTTPRequest request, std::string &userA, std::string &userB) {
	return true;
}

bool parseGetUnreadRequest(HTTPRequest request, std::string &userA, std::string &userB) {
	return true;
}

bool parseGetCandidatesRequest(HTTPRequest request, std::string &userA) {
	return true;
}

std::string makeError(std::string msg) {
	return "{\"error\":" + msg + "\"}";
}

HTTPResponse MatchRequestHandler::handleNoMatch(HTTPRequest &request) {
	return HTTPResponse();
}

HTTPResponse MatchRequestHandler::handleLogout(HTTPRequest &request) {
	return HTTPResponse();
}

HTTPResponse MatchRequestHandler::handleLogin(HTTPRequest request) {
	std::string email;
	std::string password;
	std::string token;
	parseLoginRequest(request, email, password);
	int code = login.login(email, password, token);
	std::map<std::string, std::string> headers;
	switch (code) {
		case LOGIN_ERROR:
			return HTTPResponse("400", "Error", headers, makeError("User doesn't exist or wrong password"));
		case LOGIN_OK: {
			std::string tokenJson = "{\"token\":" + token + "\"}";
			return HTTPResponse("200", "OK", headers, tokenJson);
		}
		default:
			return HTTPResponse("400", "Error", headers, makeError("Unknown Error"));
	}
}

HTTPResponse MatchRequestHandler::handleSignUp(HTTPRequest request) {
	std::string email;
	std::string password;
	UserProfile userProfile;
	parseSignUpRequest(request, email, password, userProfile);
	int code = signUp.signUp(email, password, userProfile);
	std::map<std::string, std::string> headers;
	switch (code) {
		case USER_CREATED:
			return HTTPResponse("200", "OK", headers, "");
		case 400:
			return HTTPResponse("400", "Error", headers, makeError("User already exists"));
		default:
			return HTTPResponse("400", "Error", headers, makeError("Unknown Error"));
	}
}

HTTPResponse MatchRequestHandler::handleGetCandidates(HTTPRequest request) {
	std::string email;
	parseGetCandidatesRequest(request, email);
	std::vector<UserProfile> candidates = matcher.getCandidates(email);
	// Escribir los perfiles de usuario en un Json grande
	Json::Value users;
	Json::Value array;
	for (int i = 0; i < candidates.size(); i++) {
		const Json::Value &json = candidates[i].getJson();
		array.append(json);
	}
	users["users"] = array;
	std::map<std::string, std::string> headers;
	std::string userList = utils::JsonToString(users);
	return HTTPResponse("200", "OK", headers, userList);
}

HTTPResponse MatchRequestHandler::handleSendChat(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	return HTTPResponse("200", "OK", headers, "");
}

HTTPResponse MatchRequestHandler::handleGetUnread(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	return HTTPResponse("200", "OK", headers, "");
}

HTTPResponse MatchRequestHandler::handleLike(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	return HTTPResponse("200", "OK", headers, "");
}

HTTPResponse MatchRequestHandler::handle(HTTPRequest &request) {
	std::cout << "request.toCString():" << std::endl << request.toCString() << std::endl;
	int requestType = handlers[request.getVerb()][request.getUri()];

	//try {
	switch (requestType) {
		case REQ_SIGN_UP:
			std::cout << "SIGN UP" << std::endl;
			return handleSignUp(request);
			break;
		case REQ_LOGIN:
			return handleLogin(request);
			break;
		case REQ_GET_CANDIDATES:
			return handleGetCandidates(request);
			break;
		case REQ_LIKE:
			return handleLike(request);
			break;
		case REQ_NO_MATCH:
			return handleNoMatch(request);
			break;
		case REQ_SEND_CHAT:
			return handleSendChat(request);
			break;
		case REQ_GET_UNREAD:
			return handleGetUnread(request);
			break;
		case REQ_LOGOUT:
			return handleLogout(request);
			break;
		default:
			std::map<std::string, std::string> headers;
			return HTTPResponse("404", "Bad Request", headers, "");
	}
	//} catch (...) {
	//	std::map<std::string, std::string> headers;
	//	return HTTPResponse("404", "Bad Json", headers, "");
	//}
}