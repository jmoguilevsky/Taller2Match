//
// Created by chris on 24/04/16.
//

#include "SignUp.h"
#include "../utils.h"

int SignUp::signUp(std::string email, std::string password, UserProfile userProfile) {
	int code = sharedData.newUser(userProfile);
	// Si se pudo crear en el shared, entonces lo creo en mi BD local.
	if (code == 201) {
		db.newUser(email, password);
		std::cout << "**** USERS ****" << std::endl;
		db.listAll();
		std::cout << "****************" << std::endl;
	}
	return code;
}

