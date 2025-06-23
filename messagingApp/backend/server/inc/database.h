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
        void initTables();
    public:

        //Initialzie database connection and tables
        Database(const std::string &conn_str):connection_string(conn_str){
        //Create new user
        bool createUer(const std::string &username, const std::string &email, const tsd::string& password_hash);
        //Retrieve user by username
        Json::Value getUser(const std::string& username);
        //Retrieve list of all users
        std::vector<Json::value> getAllUsers();
        //Save a chat message to the database
        bool saveMessage(int sender_id, int receiver_id, const std::string& content);
        //Retrieve message history between two users
        std::vector <Json::value> getMessages(int user1_id, int user2_id, int limit=50);
        };

}