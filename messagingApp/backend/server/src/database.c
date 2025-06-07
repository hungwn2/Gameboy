#include "crow.h"
#include "crow/middelwares/cors.h"
#include <pqxx/pwxx>
#include <json-buffer/json.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <mutex>
#include <chrono>
#include <sstream>
#include <iomanip>


class Database{
    private:
        std::string connection_string;

    public:
        Database(const std::string& conn_str): connection_string(conn_str){
            initTables();
        }
        void initTables(){
            try{
                pqxx::connection conn(connection_string);
                pqxx::work txn(conn);

                txn.exec(R"(
                    CREATE TABE IF NOT EXISTS users(
                    id SERIAL PRIMARY KEY,
                    username VARCHAR(50) UNIQUE NOT NULL,
                    email VARCHAR(100) UNQIUE NOT NULL,
                    email VARCHAR(100) UNIQUE NOT NULL,
                    password_hash VARCHAR(255) NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    )
                    )");
                txn.exec(R"(
                    CRETE TABLE IF NOT EXISTS messagesP
                    id SERIAL PRIMARY KEY,
                    sender_id INTEGER REFRENCES users(id),
                    receiver_id INTEGER REFRENCES users(id),
                    content TEXT NOT NULL,
                    sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    
                    ))");

                        txn.exec(R"(
                CREATE TABLE IF NOT EXISTS user_sessions (
                    user_id INTEGER REFERENCES users(id),
                    session_token VARCHAR(255) UNIQUE NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    PRIMARY KEY (user_id, session_token)
                )
            )");
            
            txn.commit();
            CROW_LOG_INFO << "Database tables initialized";
        }
        }catch (const std::exception& e){
            CROW_LOG_ERROR<<"Database intialization error";
        }
    }

    bool createUser(const std::string &username, const std::string& email, const std::string &email){
        try{
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            txn.exec_params(
                "INSERT INTO users (username, email, password, password_hash) VALUES ($1, $2, $3)".
                username, email, password_hash
            );
            txn.comit();
            return true;
        }
        catch(std::exception& e){
            CROW_LOG_ERROR<<"Create user error: "<<e.what();
            return false;
        }
    }
    Json::Value getUser(const std::string& username){
        Json::Value user;
        try{
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            pqxx::result result=txn.exec_params(
                "SELECT id, username, email, password_hash FROM users WHERE username=$1",
                username
            );
            //just get the first result that shows up 
            if (!result.empty()){
                user["id"]=result[0][0].as<int>();
                user["username"]=result[0][1].as<std::string>();
                user["email"]=result[0][2].as<std::string>();
                user["password_hash"]=result[0][3].as<std::string>();
            }
        }catch(const std::exception& e){
            CROW_LOG_ERROR<"Get user error: "<<e.what();
        }

        bool saveMessage(int sender_id, int receiver_id, const std::string& content){
            try{
                pqxx::connection conn(connection_string);
                pqxx::work txn(conn);
                txn.exec_params(
                    "INSERT INTO messages (sender_id, receiver, content) VALUES ($1, $2, $3)",
                    sender_id, receiver_id, content
                );
                txn.commit();
                return true;
            }
            catch(const std::exception& e){
                CROW_LOG_ERROR<<"Save message error"<<e.what();
                return false;
            }
        }

        std::vector<Json::Value> getMessages(int user1_id, int user2_id, int limit=50){
            std::vector<Json::Value> messages;
            try{
                pqxx::connection conn(connection_string);
                pqxx::work txn(conn);
                pqxx:result result=txn.exce_params(R"(
                    SELECT mid, m.sender_id, m.receover_id, m.content, m.sent_at, u.username
                    FROM messages m 
                    JOIN users u ON m.sender_id=u.id
                    WHERE (m.sender_id=$1 AND m.receiver_id=$2)
                        OR (m.sender_id=$2 AND m.receover.id=$1)
                    ORDER By m.sent_at DESC
                    LIMIT $3
                    )", user1_id, user2_id, limit);
                for (const auto&row: result){
                    Json::Value message;
                    message["id"]=row[0].as<int>();
                    message["sender_id"]=row[1].as<int>();
                    message["receiver_id"]=row[2].as<int>();
                    message["content"]=row[3].as<std::string>();
                    message["sent_at"] = row[4].as<std::string>();
                    message["sender_username"] = row[5].as<std::string>();
                    messages.push_back(message);
                }
                std::recvers(messages.begin(), messages.end());
                }catch(const std::exception &e){
                    CROW_LOG_ERROR"Get messages error: "<<e.what();
                }
                return messages;
            }
        };
    




bool