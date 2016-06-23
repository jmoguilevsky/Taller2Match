//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_USERSHTTP_H
#define APPSERVER_USERSHTTP_H

#include "../HTTP/HTTPRequest.h"
#include "../HTTP/HTTPResponse.h"
#include "../MatchData/ProfilesDatabase.h"
#include "../MatchData/Matcher.h"
#include "../MatchData/ConnectedUsers.h"

//! Esta clase maneja los requests HTTP que tienen que ver con login, logout, etc...

class UsersHTTP {

	ProfilesDatabase& profilesDatabase;

	ConnectedUsers& connected;

	const Matcher& matcher;

	//! Handler para registrar un nuevo usuario en el servidor.
	HTTPResponse handleSignUp(HTTPRequest request);
	//! Handler para que un usuario se conecte al servidor.
	HTTPResponse handleLogin(HTTPRequest request);
	//! Handler para que un usuario se desconecte del servidor.
	HTTPResponse handleLogout(HTTPRequest request);
	//! Handler para la actualización del perfil de un usuario.
	HTTPResponse handleUpdateProfile(HTTPRequest request);
	//! Handler para la actualización de la foto de perfil de un usuario.
	HTTPResponse handleUpdatePhoto(HTTPRequest request);

public:

	UsersHTTP(ConnectedUsers& connected, ProfilesDatabase& users, const Matcher& matcher): connected(connected), profilesDatabase(users), matcher(matcher){};

	HTTPResponse handle(HTTPRequest request);

};


#endif //APPSERVER_USERSHTTP_H
