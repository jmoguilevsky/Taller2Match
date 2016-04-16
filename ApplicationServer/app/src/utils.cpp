//
// Created by chris on 16/04/16.
//

#include "utils.h"

#include <string>
#include "../mongoose-master/mongoose.h"

std::string bufToString(struct mg_connection* connection){
	struct mbuf* io = &connection->recv_mbuf;
	std::string str = io -> buf;
	str[str.size()-1] = '\0';
	mbuf_remove(io, io->len);
	return str;
}
