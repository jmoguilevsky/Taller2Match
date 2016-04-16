//
// Created by chris on 15/04/16.
//

#include "ClientHandler.h"
#include "utils.h"

ClientHandler::ClientHandler(struct mg_connection *connectionToClient, const std::string& sharedAddress) {
	// Cuando se inicia la conexión con el cliente, le creo también su propia conexión al shared.
	struct mg_mgr *mgr = connectionToClient->mgr;
	struct mg_connect_opts opts;
	opts.user_data = (void*) this;
	this -> connectionToClient = connectionToClient;
	connectionToShared = mg_connect_opt(mgr, sharedAddress.c_str(), sharedHandler,opts);
	this -> waiting = false;
}

void ClientHandler::handleLastRequest(const std::string &requestAnswerFromShared) {
	// Procesa un request, después de haber pedido la info al shared, y haber recibido
	// la respuesta.
	// TODO remove this request from the queue
	// TODO switch para originalRequest, y llamar a la función/método que corresponda.
	// TODO y pasarle la info que mandó el shared.
	// TODO usando connectionToClient, mandar la respuesta.

	// Cuando termino de procesar este request, puedo empezar con el siguiente.
	this->waiting = false;
}

bool ClientHandler::isWaiting() {
	// Devuelve true si el ClientHandler está haciendo algo, ya sea esperando
	// por una respuesta del shared, o procesando un request por su cuenta.
	return this->waiting;
}

void ClientHandler::sendNextRequest() {
	// Envia el siguiente request para el shared, si es que hay alguno.
	// TODO send this request to shared server
	this->waiting = true; // Siempre hay que setear esto para
	// no procesar dos request al mismo tiempo y que haya lio.
}

void ClientHandler::addRequest(std::string originalRequest) {
	// Agrega un request a la cola de requests.
	// Si hace falta, de acuerdo al request que me llegó, veo qué hay
	// que pedirle al shared para completarlo.
	std::string requestToShared = getRequestToShared(originalRequest);
	requestQueue.push(requestToShared);
}

std::string ClientHandler::getRequestToShared(const std::string &originalRequest) {
	// De acuerdo al request que me llegó, devuelvo qué hay que pedirle al shared,
	// si es necesario.
	// TODO ver qué manda el client, y qué hay que pedirle al shared.
	// TODO DEFINIR API client - app server
	return "REQUEST";
}

void ClientHandler::handle(struct mg_connection *Connection, int ev) {
	if(ev == MG_EV_RECV){
		std::string request = utils::bufToString(connectionToClient);
		// Cuando llega un request del client, se lo paso al ClientHandler para que se encargue.
		addRequest(request);
		//TODO ? esto se podría hacer acá directamente.
	}
}

void ClientHandler::sharedHandler(struct mg_connection *connectionToShared, int ev, void *p) {

	ClientHandler* clientHandler = ((ClientHandler*)connectionToShared -> user_data);

	if(ev == MG_EV_RECV){
		// Recibí una respuesta del shared, se la paso al clientHandler para que
		// trabaje.
		std::string requestAnswerFromShared = utils::bufToString(connectionToShared);
		clientHandler -> handleLastRequest(requestAnswerFromShared);
	}
	if(!clientHandler->isWaiting()){
		// Si no estoy esperando una respuesta del shared, ni estoy trabajando,
		// puedo mandar el siguiente request al shared.
		clientHandler -> sendNextRequest();
	}
}