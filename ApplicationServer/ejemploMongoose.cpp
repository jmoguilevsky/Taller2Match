#include "mongoose-master/mongoose.h"
#include <iostream>


static const char * s_http_port = "8000";

static void ev_handler(struct mg_connection* c, int ev, void* p) {
	if (ev == MG_EV_HTTP_REQUEST) {
		
		// Representa un mensaje http.
		struct http_message* hm = (struct http_message*) p;
		
		// No estoy seguro del tamanio de la reply, si es fijo o puede
		// definirse a gusto.
		char reply[100];
		
		sleep(1);

		snprintf(reply, sizeof(reply), "{ \"uri\": \"%.*s\" } \n",
			(int) hm->uri.len, hm->uri.p);
		
		// Envia un string formateado a lo printf a la conexion
		mg_printf(c, "HTTP/1.1 200 OK \r\n"
			     "Content-Type: application/json\r\n"
			     "Content-Lenght: %d\r\n"
			     "\r\n"
			     "%s",
			     (int) strlen(reply), reply);
	}
}

int main(void) {
	
	// Este es el struct correspondiente al event manager de Mongoose
	struct mg_mgr mgr;

	// Representa la conexion Mongoose
	struct mg_connection* nc;
	
	// Inicializa el manager. 
	mg_mgr_init(&mgr, NULL);

	// Crea una conexion escuchando. Le paso la funcion ev_handler por parametro.
	nc = mg_bind(&mgr, s_http_port, ev_handler);

	// Attachea un event-handler HTTP a una conexion dada
	mg_set_protocol_http_websocket(nc);
	
	// Habilita el multithreading para una conexion dada. Mongoose crea un thread nuevo y
	// ejecuta el ev_handler pasado por parametro en mg_bind
	mg_enable_multithreading(nc);

	std::cout << "Starting multi-threaded server on port" <<  s_http_port << std::endl;
	while (true) {
		// Desencola los eventos. Recibe el puntero al manager y la cant
		// maxima de milisegundos a dormir
		mg_mgr_poll(&mgr, 3000);
	}	
	
	// Elimina el manager.
	mg_mgr_free(&mgr);

	return 0;
}
