//
// Created by chris on 24/04/16.
//

#include "MatchesDB.h"

#define ONE_DAY 86400 // En segundos
#define LIKES_PER_DAY 10

int MatchesDB::likeUser(const std::string &user1, const std::string &user2) {
	// TODO return defines según cómo queda la cosa.

	std::vector<std::string> likesLimit = utils::valuesAsVector(likeLimit,
	                                                            user1);
	struct tm lastTime = utils::stringToTime(
			likesLimit[0]); // Timestamp de la última vez que se reinició el límite de likes.
	int likesLeft = utils::stringToInt(
			likesLimit[1]); // Nro. de likes que quedan en este período de 24 hs.
	struct tm currTime = utils::currentDateTime();
	int diff = utils::diffTimeInSeconds(currTime, lastTime);
	if (diff < ONE_DAY && likesLeft == 0) {
		// Se acabaron los likes por hoy...
		return -1;
	}
	if (diff >= ONE_DAY) {
		likesLeft = LIKES_PER_DAY;
		lastTime = currTime; // Reinicio el límite de likes
	}
	if (!utils::valueInDBList(noMatches, user1, user2)) {
		utils::appendValue(likes, user1, user2);
		int currLikes = stringToInt(likesReceived->get(user2));
		likesReceived->save(user2, utils::intToString(
				currLikes++)); // Le sumo un like recibido al user2
		likesLeft--; // Le queda un like menos al user1
		likeLimit->save(user1, utils::timeToString(lastTime) + "," +
		                       utils::intToString(likesLeft));
	}
	if (utils::valueInDBList(likes, user1, user2) &&
	    utils::valueInDBList(likes, user2, user1)) {
		// Si user1 like user2, y user2 like user1 -> MATCH
		utils::appendValue(matches, user1, user2);
		utils::appendValue(matches, user2, user1);
	}
	return 0;
}

int MatchesDB::rejectUser(const std::string &user1, const std::string &user2) {
	if (!utils::valueInDBList(likes, user1, user2) &&
	    !utils::valueInDBList(matches, user1, user2)) {
		utils::appendValue(noMatches, user1, user2);
	}
	// TODO valor de retorno?
	return 0;
}

int MatchesDB::getLikesReceived(const std::string &user) {
	return utils::stringToInt(likesReceived->get(user));
}

std::vector<std::string> MatchesDB::getLikes(const std::string &user) {
	return utils::valuesAsVector(likes, user);
}

std::vector<std::string> MatchesDB::getMatches(const std::string &user) {
	// Devuelve los matches para el usuario.
	return utils::valuesAsVector(matches, user);
}

std::vector<std::string> MatchesDB::getNoMatches(const std::string &user) {
	// Devuelve los users que user rechazó.
	return utils::valuesAsVector(noMatches, user);
}