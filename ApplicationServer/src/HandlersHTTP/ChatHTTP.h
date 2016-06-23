//
// Created by chris on 12/05/16.
//

#ifndef APPSERVER_CHATHTTP_H
#define APPSERVER_CHATHTTP_H


#include "../HTTP/HTTP.h"
#include "../HTTP/HTTPResponse.h"
#include "../HTTP/HTTPRequest.h"
#include "../MatchData/Chat.h"
#include "../MatchData/Matcher.h"
#include "../MatchData/ConnectedUsers.h"
//! Esta clase maneja los requests HTTP del chat.

class ChatHTTP {

    Matcher &matcher;

    ConnectedUsers& connected;

    Chat &chat;

    //! Handler para enviar un mensaje en el chat entre dos usuarios.
    HTTPResponse handleSendChat(HTTPRequest request);

    //! Handler para obtener el historial completo de una conversación entre dos usuarios.
    HTTPResponse handleGetHistory(HTTPRequest request);

public:

    ChatHTTP(Matcher &matcher, Chat &chat, ConnectedUsers &connected)
            : matcher(matcher), chat(chat), connected(connected) { }

    HTTPResponse handle(HTTPRequest request);

    //! Handler para el request para obtener los mensajes que aún no recibió un usuario.
    HTTPResponse handleGetNew(HTTPRequest request);
};


#endif //APPSERVER_CHATHTTP_H
