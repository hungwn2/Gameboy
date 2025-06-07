
#include <map>
#include <iostream>

class WebSocketManager{
    private:
        std::unordered_map<int, corw::websocket::connection*> user_connections;
        std::unordered_map<crow::websocket::connection*, int> connectin_users;
        std::mutex connections_mutex;


    public:
        void addConnection(int user_id, crow::websocket::connection* conn);
        void removeConnection(crow::websocket::connection* conn);
        void sendToUser(int user_id, const std::string &message);
        void broadcastMessage(cons Json::value& mmessage_data);
        
}