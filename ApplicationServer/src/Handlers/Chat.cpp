//
// Created by chris on 06/05/16.
//

#include "Chat.h"

std::string buildKey(std::string userId, std::string otherUserId){
    if (userId < otherUserId) return userId + otherUserId;
    return otherUserId + userId;
}

std::string Chat::getHistory(std::string userId, std::string otherUserId) const {
    std::string chatKey = buildKey(userId,otherUserId);
    std::string historyStr = chat_db->values_as_string(chatKey);
    return historyStr;
}

void Chat::sendMessage(std::string userId, std::string otherUserId, std::string content) {
    std::string chatKey = buildKey(userId,otherUserId);
    Json::Value msgJson("message");
    Json::Value msgContent = util::stringToJson(content);
    msgJson["content"] = msgContent["content"];
    msgJson["from"] = userId;
    msgJson["to"] = otherUserId;
    msgJson["time"] = "now"; // TODO poner la hora de verdad acá!
    std::string msgString = util::JsonToString(msgJson);
    std::cout << "msgString: \"\n" << msgString << "\"" << std::endl;
//    append(*chat_db,chatKey,msgString);
}