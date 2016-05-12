#include "MatchRequestHandler.h"
#include "../DB/ChatMessage.h"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define URI_LOGIN "/login"
#define URI_LOGOUT "/logout"
#define URI_SIGNUP "/signup"
#define URI_CANDIDATES "/candidates"
#define URI_GET_UNREAD "/unread"
#define URI_SEND_CHAT "/chat"
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
	handlers[HTTP_POST][URI_LOGOUT] = REQ_LOGOUT;
	handlers[HTTP_POST][URI_SIGNUP] = REQ_SIGN_UP;
	handlers[HTTP_POST][URI_LIKE] = REQ_LIKE;
	handlers[HTTP_POST][URI_NOMATCH] = REQ_NO_MATCH;
	handlers[HTTP_POST][URI_SEND_CHAT] = REQ_SEND_CHAT;
	handlers[HTTP_GET][URI_CANDIDATES] = REQ_GET_CANDIDATES;
	handlers[HTTP_GET][URI_GET_UNREAD] = REQ_GET_UNREAD;

}

void parseSendChatRequest(HTTPRequest request, ChatMessage &msg) {
	Json::Value msgJson = utils::stringToJson(request.getBody());
	std::string userFrom = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
	msgJson["message"]["from"] = userFrom;
	msgJson["message"]["read"] = "no";
	msg.fromJson(msgJson);
}

bool MatchRequestHandler::checkCredentials(HTTPRequest request) {
	std::string auth = request.getHeader("Authorization");
	Json::Value authInfo = utils::stringToJson(auth);
	std::string email = authInfo["email"].asString();
	std::string tok = authInfo["token"].asString();
	return login.checkToken(email, tok);
}

MatchRequestHandler::~MatchRequestHandler() { }

bool parseLoginRequest(HTTPRequest request, std::string &user, std::string &pass) {
	Json::Value userInfo = utils::stringToJson(request.getBody());
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

bool parseLikeRequest(HTTPRequest request, std::string &userB) {
	Json::Value userInfo = utils::stringToJson(request.getBody());
	userB = userInfo["user"]["email"].asString();
	return true;
}

bool parseNoMatchRequest(HTTPRequest request, std::string &userA, std::string &userB) {
	return true;
}

bool parseGetUnreadRequest(HTTPRequest request, std::string &userB) {
	parseLikeRequest(request, userB);
}

bool parseGetCandidatesRequest(HTTPRequest request, std::string &userA) {
	return true;
}

std::string makeError(std::string msg) {
	return "{\"error\":" + msg + "\"}";
}

HTTPResponse MatchRequestHandler::handleNoMatch(HTTPRequest &request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		//std::string email;
		//parseGetCandidatesRequest(request, email);
		std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
		std::string userB;
		parseLikeRequest(request, userB);
		std::cout << "USER B is " << userB << std::endl;
		int code = matcher.postNoMatch(email, userB);
		std::cout << "OK";
		return HTTPResponse("200", "OK", headers, "");
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
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
		case ALREADY_LOGGED_IN:
			return HTTPResponse("400", "Error", headers, makeError("User already logged in"));
		default:
			return HTTPResponse("400", "Error", headers, makeError("Unknown Error"));
	}
}

HTTPResponse MatchRequestHandler::handleLogout(HTTPRequest &request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
		login.logout(email);
		return HTTPResponse("200", "OK", headers, "");
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
}

HTTPResponse MatchRequestHandler::handleSignUp(HTTPRequest request) {
	std::string email;
	std::string password;
	UserProfile userProfile;
	parseSignUpRequest(request, email, password, userProfile);
	int code = login.signUp(email, password, userProfile);
	std::map<std::string, std::string> headers;
	switch (code) {
		case 201:
			return HTTPResponse("200", "OK", headers, "");
		case 400:
			return HTTPResponse("400", "Error", headers, makeError("User already exists"));
		default:
			return HTTPResponse("400", "Error", headers, makeError("Unknown Error"));
	}
}

HTTPResponse MatchRequestHandler::handleGetCandidates(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		//std::string email;
		//parseGetCandidatesRequest(request, email);
		std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
		std::vector<UserProfile> candidates = matcher.getCandidates(email);
		// Escribir los perfiles de usuario en un Json grande
		Json::Value users;
		Json::Value array;
		for (int i = 0; i < candidates.size(); i++) {
			const Json::Value &json = candidates[i].getJson();
			array.append(json);
		}
		users["users"] = array;

		std::string userList = utils::JsonToString(users);
		return HTTPResponse("200", "OK", headers, userList);
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
}

HTTPResponse MatchRequestHandler::handleSendChat(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		ChatMessage msg;
		parseSendChatRequest(request, msg);
		std::cout << utils::JsonToString(msg.toJson()) << std::endl;
		chat.sendMessage(msg);
		return HTTPResponse("200", "OK", headers, "");
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
}

HTTPResponse MatchRequestHandler::handleGetUnread(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		std::string userB;
		std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
		parseGetUnreadRequest(request, userB);
		std::vector<ChatMessage> unread = chat.getUnread(email, userB);
		Json::Value messages;
		Json::Value array;
		for (int i = 0; i < unread.size(); i++) {
			array.append(unread[i].toJson());
		}
		messages["messages"] = array;
		std::string toSend = utils::JsonToString(messages);
		return HTTPResponse("200", "OK", headers, toSend);
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
}

HTTPResponse MatchRequestHandler::handleLike(HTTPRequest request) {
	std::map<std::string, std::string> headers;
	if (checkCredentials(request)) {
		//std::string email;
		//parseGetCandidatesRequest(request, email);
		std::string email = utils::stringToJson(request.getHeader("Authorization"))["email"].asString();
		std::string userB;
		parseLikeRequest(request, userB);
		std::cout << "USER B is " << userB << std::endl;
		int code = matcher.postLike(email, userB);
		std::cout << "OK";
		return HTTPResponse("200", "OK", headers, "");
	} else {
		return HTTPResponse("409", "Unauthorized", headers, makeError("Invalid credentials"));
	}
}

HTTPResponse MatchRequestHandler::handle(HTTPRequest &request) {
	std::cout << "request.toCString():" << std::endl << request.toCString() << std::endl;
	int requestType = handlers[request.getVerb()][request.getUri()];

	//try {
	switch (requestType) {
		case REQ_SIGN_UP:
			std::cout << "<<< SIGN UP >>>" << std::endl;
			return handleSignUp(request);
			break;
		case REQ_LOGIN:
			std::cout << "<<< LOGIN >>>" << std::endl;
			return handleLogin(request);
			break;
		case REQ_GET_CANDIDATES:
			std::cout << "<<< GET CANDIDATES >>>" << std::endl;
			return handleGetCandidates(request);
			break;
		case REQ_LIKE:
			std::cout << "<<< LIKE >>>" << std::endl;
			return handleLike(request);
			break;
		case REQ_NO_MATCH:
			std::cout << "<<< NO MATCH >>>" << std::endl;
			return handleNoMatch(request);
			break;
		case REQ_SEND_CHAT:
			std::cout << "<<< SEND CHAT >>>" << std::endl;
			return handleSendChat(request);
			break;
		case REQ_GET_UNREAD:
			std::cout << "<<< GET UNREAD >>>" << std::endl;
			return handleGetUnread(request);
			break;
		case REQ_LOGOUT:
			std::cout << "<<< LOGOUT >>>" << std::endl;
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

