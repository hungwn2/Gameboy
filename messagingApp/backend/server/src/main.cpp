#include "crow.h"
#include "crow_all.h"
#include "crow/middlewares/cors.h"
#include <pqxx/pqxx>
#include <json/json.h>
#include "Database.hh"
#include "WebSocketManager.h"
#include "Auth.h"


class Database {
private:
    std::string connection_string;
    
public:
    Database(const std::string& conn_str) : connection_string(conn_str) {
        initTables();
    }
    
    void initTables() {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            // Users table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS users (
                    id SERIAL PRIMARY KEY,
                    username VARCHAR(50) UNIQUE NOT NULL,
                    email VARCHAR(100) UNIQUE NOT NULL,
                    password_hash VARCHAR(255) NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            
            // Messages table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS messages (
                    id SERIAL PRIMARY KEY,
                    sender_id INTEGER REFERENCES users(id),
                    receiver_id INTEGER REFERENCES users(id),
                    content TEXT NOT NULL,
                    sent_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            
            // Online users table (for session management)
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
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Database initialization error: " << e.what();
        }
    }
    
    bool createUser(const std::string& username, const std::string& email, const std::string& password_hash) {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            txn.exec_params(
                "INSERT INTO users (username, email, password_hash) VALUES ($1, $2, $3)",
                username, email, password_hash
            );
            
            txn.commit();
            return true;
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Create user error: " << e.what();
            return false;
        }
    }
    
    Json::Value getUser(const std::string& username) {
        Json::Value user;
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            pqxx::result result = txn.exec_params(
                "SELECT id, username, email, password_hash FROM users WHERE username = $1",
                username
            );
            
            if (!result.empty()) {
                user["id"] = result[0][0].as<int>();
                user["username"] = result[0][1].as<std::string>();
                user["email"] = result[0][2].as<std::string>();
                user["password_hash"] = result[0][3].as<std::string>();
            }
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Get user error: " << e.what();
        }
        return user;
    }
    
    std::vector<Json::Value> getAllUsers() {
        std::vector<Json::Value> users;
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            pqxx::result result = txn.exec("SELECT id, username, email FROM users ORDER BY username");
            
            for (const auto& row : result) {
                Json::Value user;
                user["id"] = row[0].as<int>();
                user["username"] = row[1].as<std::string>();
                user["email"] = row[2].as<std::string>();
                users.push_back(user);
            }
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Get all users error: " << e.what();
        }
        return users;
    }
    
    bool saveMessage(int sender_id, int receiver_id, const std::string& content) {
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            txn.exec_params(
                "INSERT INTO messages (sender_id, receiver_id, content) VALUES ($1, $2, $3)",
                sender_id, receiver_id, content
            );
            
            txn.commit();
            return true;
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Save message error: " << e.what();
            return false;
        }
    }
    
    std::vector<Json::Value> getMessages(int user1_id, int user2_id, int limit = 50) {
        std::vector<Json::Value> messages;
        try {
            pqxx::connection conn(connection_string);
            pqxx::work txn(conn);
            
            pqxx::result result = txn.exec_params(R"(
                SELECT m.id, m.sender_id, m.receiver_id, m.content, m.sent_at, u.username
                FROM messages m
                JOIN users u ON m.sender_id = u.id
                WHERE (m.sender_id = $1 AND m.receiver_id = $2) 
                   OR (m.sender_id = $2 AND m.receiver_id = $1)
                ORDER BY m.sent_at DESC
                LIMIT $3
            )", user1_id, user2_id, limit);
            
            for (const auto& row : result) {
                Json::Value message;
                message["id"] = row[0].as<int>();
                message["sender_id"] = row[1].as<int>();
                message["receiver_id"] = row[2].as<int>();
                message["content"] = row[3].as<std::string>();
                message["sent_at"] = row[4].as<std::string>();
                message["sender_username"] = row[5].as<std::string>();
                messages.push_back(message);
            }
            
            // Reverse to get chronological order
            std::reverse(messages.begin(), messages.end());
        } catch (const std::exception& e) {
            CROW_LOG_ERROR << "Get messages error: " << e.what();
        }
        return messages;
    }
};

class WebSocketManager {
private:
    std::unordered_map<int, crow::websocket::connection*> user_connections;  // user_id -> connection
    std::unordered_map<crow::websocket::connection*, int> connection_users;  // connection -> user_id
    std::mutex connections_mutex;
    
public:
    void addConnection(int user_id, crow::websocket::connection* conn) {
        std::lock_guard<std::mutex> lock(connections_mutex);
        user_connections[user_id] = conn;
        connection_users[conn] = user_id;
        CROW_LOG_INFO << "User " << user_id << " connected via WebSocket";
    }
    
    void removeConnection(crow::websocket::connection* conn) {
        std::lock_guard<std::mutex> lock(connections_mutex);
        auto it = connection_users.find(conn);
        if (it != connection_users.end()) {
            int user_id = it->second;
            user_connections.erase(user_id);
            connection_users.erase(it);
            CROW_LOG_INFO << "User " << user_id << " disconnected from WebSocket";
        }
    }
    
    void sendToUser(int user_id, const std::string& message) {
        std::lock_guard<std::mutex> lock(connections_mutex);
        auto it = user_connections.find(user_id);
        if (it != user_connections.end() && it->second) {
            it->second->send_text(message);
        }
    }
    
    void broadcastMessage(const Json::Value& message_data) {
        Json::StreamWriterBuilder builder;
        std::string message_str = Json::writeString(builder, message_data);
        
        int receiver_id = message_data["receiver_id"].asInt();
        sendToUser(receiver_id, message_str);
    }
};

// Simple hash function for password (use proper hashing in production)
std::string hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    size_t hash_value = hasher(password);
    std::ostringstream oss;
    oss << std::hex << hash_value;
    return oss.str();
}

int main() {
    // Database connection string - modify as needed
    std::string db_conn = "postgresql://username:password@localhost/messaging_db";
    Database db(db_conn);
    WebSocketManager ws_manager;
    
    crow::App<crow::CORSHandler> app;
    
    // Configure CORS
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .headers("*")
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .origin("http://localhost:3000");  // React dev server
    
    // User registration
    CROW_ROUTE(app, "/api/register").methods("POST"_method)
    ([&db](const crow::request& req) {
        Json::Value root;
        Json::Reader reader;
        
        if (!reader.parse(req.body, root)) {
            return crow::response(400, "Invalid JSON");
        }
        
        std::string username = root["username"].asString();
        std::string email = root["email"].asString();
        std::string password = root["password"].asString();
        
        if (username.empty() || email.empty() || password.empty()) {
            return crow::response(400, "Missing required fields");
        }
        
        std::string password_hash = hashPassword(password);
        
        if (db.createUser(username, email, password_hash)) {
            Json::Value response;
            response["success"] = true;
            response["message"] = "User created successfully";
            
            Json::StreamWriterBuilder builder;
            return crow::response(201, Json::writeString(builder, response));
        } else {
            return crow::response(409, "User already exists");
        }
    });
    
    // User login
    CROW_ROUTE(app, "/api/login").methods("POST"_method)
    ([&db](const crow::request& req) {
        Json::Value root;
        Json::Reader reader;
        
        if (!reader.parse(req.body, root)) {
            return crow::response(400, "Invalid JSON");
        }
        
        std::string username = root["username"].asString();
        std::string password = root["password"].asString();
        
        Json::Value user = db.getUser(username);
        if (user.empty()) {
            return crow::response(401, "Invalid credentials");
        }
        
        std::string provided_hash = hashPassword(password);
        if (provided_hash != user["password_hash"].asString()) {
            return crow::response(401, "Invalid credentials");
        }
        
        Json::Value response;
        response["success"] = true;
        response["user"]["id"] = user["id"];
        response["user"]["username"] = user["username"];
        response["user"]["email"] = user["email"];
        
        Json::StreamWriterBuilder builder;
        return crow::response(200, Json::writeString(builder, response));
    });
    
    // Get all users
    CROW_ROUTE(app, "/api/users").methods("GET"_method)
    ([&db](const crow::request& req) {
        std::vector<Json::Value> users = db.getAllUsers();
        
        Json::Value response;
        response["users"] = Json::Value(Json::arrayValue);
        for (const auto& user : users) {
            response["users"].append(user);
        }
        
        Json::StreamWriterBuilder builder;
        return crow::response(200, Json::writeString(builder, response));
    });
    
    // Get messages between two users
    CROW_ROUTE(app, "/api/messages/<int>/<int>").methods("GET"_method)
    ([&db](int user1_id, int user2_id) {
        std::vector<Json::Value> messages = db.getMessages(user1_id, user2_id);
        
        Json::Value response;
        response["messages"] = Json::Value(Json::arrayValue);
        for (const auto& message : messages) {
            response["messages"].append(message);
        }
        
        Json::StreamWriterBuilder builder;
        return crow::response(200, Json::writeString(builder, response));
    });
    
    // Send message
    CROW_ROUTE(app, "/api/messages").methods("POST"_method)
    ([&db, &ws_manager](const crow::request& req) {
        Json::Value root;
        Json::Reader reader;
        
        if (!reader.parse(req.body, root)) {
            return crow::response(400, "Invalid JSON");
        }
        
        int sender_id = root["sender_id"].asInt();
        int receiver_id = root["receiver_id"].asInt();
        std::string content = root["content"].asString();
        
        if (db.saveMessage(sender_id, receiver_id, content)) {
            // Broadcast message via WebSocket
            Json::Value message_data;
            message_data["type"] = "new_message";
            message_data["sender_id"] = sender_id;
            message_data["receiver_id"] = receiver_id;
            message_data["content"] = content;
            message_data["sent_at"] = "now"; // In real app, get from DB
            
            ws_manager.broadcastMessage(message_data);
            
            return crow::response(201, "Message sent");
        } else {
            return crow::response(500, "Failed to send message");
        }
    });
    
    // WebSocket endpoint
    CROW_ROUTE(app, "/ws").websocket()
        .onopen([&ws_manager](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "WebSocket connection opened";
        })
        .onclose([&ws_manager](crow::websocket::connection& conn, const std::string& reason) {
            ws_manager.removeConnection(&conn);
            CROW_LOG_INFO << "WebSocket connection closed: " << reason;
        })
        .onmessage([&ws_manager](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            if (!is_binary) {
                Json::Value root;
                Json::Reader reader;
                
                if (reader.parse(data, root)) {
                    if (root["type"].asString() == "auth") {
                        int user_id = root["user_id"].asInt();
                        ws_manager.addConnection(user_id, &conn);
                    }
                }
            }
        });
    
    app.port(8080).multithreaded().run();
    
    return 0;
}