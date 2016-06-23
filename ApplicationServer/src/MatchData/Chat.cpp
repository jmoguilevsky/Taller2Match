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
    Json::Value notif;
    Json::Value msg;
    msg["message"] = content;
    msg["from"] = userId;
    msg["time"] = "now";
    notif["message"] = msg;
    std::cout << "jsontostring: " << util::JsonToString(notif) << std::endl;
    notifications_db -> append_value(otherUserId, util::JsonToString(notif));
    std::cout << "Notifications for user: " << otherUserId << std::endl <<
    notifications_db -> values_as_string(otherUserId) << std::endl;
    return msgString;
}

Json::Value Chat::getNewForUser(std::string userId) {
    Json::Value array = util::stringToJson(notifications_db -> values_as_string(userId));
    notifications_db -> erase_key(userId);
    for (int i = 0; i < array . size(); i++) {
        //notifications_db -> remove_value(userId,util::JsonToString(array[i])); // Borro las notificationes que ya estoy mandando
    }
    return array;
}
