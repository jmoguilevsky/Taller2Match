//
// Created by chris on 24/04/16.
//

#ifndef APPSERVER_HTTPRESPONSE_H
#define APPSERVER_HTTPRESPONSE_H

#include <string>
#include <map>

#define HTTP_VERSION "HTTP/1.1"

//! Una respuesta HTTP.

class HTTPResponse {
    std::string message;
    std::string body;
    int code;
public:

    //! Crea un HTTPResponse a partir de un código, la phrase HTTP (OK, Error, etc.), un map de headers (como en el HTTPRequest), y un body.
    HTTPResponse(std::string code, std::string phrase,
                 std::map<std::string, std::string> headers, std::string body);
    //! Devuelve el HTTPResponse completo como un char* de C.
    HTTPResponse();

    //! Crea un HTTPResponse a partir de un httm_message de Mongoose
    HTTPResponse(struct http_message *hm);

    const char *toCString();

    std::string toString();

    //! Devuelve el cuerpo del mensaje como string.
    std::string getBody();

    //! Devuelve el código de respuesta HTTP.
    int getCode();
};


#endif //APPSERVER_HTTPRESPONSE_H
