#pragma once
#include <map>
#include <iostream>
#include <mutex>
#include <stdint.h>
#include <json.h>
#include <crow/websocket.h> // Add this include for crow::websocket::connection

class WebSocketManager{
    public:
        static std::unordered_map<int, void*> user_connections;
        static std::unordered_map<void*, int> connection_users;
        static std::mutex connections_mutex;


        void addConnection(int user_id, crow::websocket::connection* conn);
        void removeConnection(crow::websocket::connection* conn);
        void sendToUser(int user_id, const std::string &message);
        void broadcastMessage(const Json::value& mmessage_data);
        
};