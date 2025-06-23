#include "WebSocketManager.h"
    

void addConnection(int user_id, void* conn){
    std::lock_guard<std::mutex> lock(connections_mutex);
    WebSocketManager::user_connections[user_id]=conn;
    connection_users[conn]=user_id;
    CROW_LOG_INFO<<"User "<<user_id<< "connected";
}

void removeConnection(void* conn){
    std::lock_guard<std::mutex> lock (connections_mutex);
    auto it=connection_users.find(conn);
    if (it!=connections_users.end()){
        int user_id=it->second;
        user_connections.erase(user_id);
        connection_users.erase(it);
        CROW_LOG_INFO<<"user "<<user_id<<"disconnected";
    }
}

void sendToUser(int user_id, const std::string &message){
        std::lock_guard<std::mutex> lock (connections_mutex);
        auto it= user_connections.find(user_id);
        if (it!=user_connections.end() &&it->second){
            it->second->send_text(message);
        }
}

void broadcastMessage(const Json::Value& message_data){
    Json::StreamWriterBuilder builder;
    std::string message_str = Json::writeString(builder, message_data);
    int receiver_id=message_data["recevier_id"].asInt();
    sendToUser(receiver_id, message_str);
}