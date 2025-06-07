#include <iostream>
#include <stdint.h>
#include <string.h>
#include <pqxx/pqxx>
#include "crow_all.h"
#include <json/json.h>
#include <vector>
#include <mutex>
#include <mutex>
#include <chrono>
#include <sstream>
#include <iomanip>


class Database{
    private:
        std::string connection_string;
    public:
        Database(const std::string &conn_str):connection_string(conn_str){
        void initTables();
        bool createUer(const std::string &username, const std::string &email, const tsd::string& password_hash);
        Json::Value getUser(const std::string& username);
        std::vector<Json::value> getAllUsers();

        bool saveMessage(int sender_id, int receiver_id, const std::string& content);
        std::vector <Json::value> getMessages(int user1_id, int user2_id, int limit=50);
        };

}