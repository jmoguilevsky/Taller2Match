//
// Created by chris on 06/05/16.
//

#include "Chat.h"
#include "../HandlersHTTP/Notifier.h"

std::string buildKey(std::string userId, std::string otherUserId){
    if (userId < otherUserId) return userId + ":" + otherUserId;
    return otherUserId + ":" + userId;
}

std::string Chat::getHistory(std::string userId, std::string otherUserId) const {
    std::string chatKey = buildKey(userId,otherUserId);
    std::string historyStr = chat_db->values_as_string(chatKey);
    return historyStr;
}

std::string Chat::sendMessage(std::string userId, std::string otherUserId, std::string content) {
    std::string chatKey = buildKey(userId,otherUserId);
    Json::Value msgJson;
    Json::Value main;
    msgJson["content"] = content;
    msgJson["from"] = userId;
    msgJson["to"] = otherUserId;
    msgJson["time"] = "now"; // TODO poner la hora de verdad acá!
    main["message"] = msgJson;
    std::string msgString = util::JsonToString(main);
    chat_db->append_value(chatKey, msgString);
    return msgString;
}